#include "Juce8WebViewPlugin/PluginProcessor.h"
#include "Juce8WebViewPlugin/PluginEditor.h"

namespace webview_plugin
{

    namespace
    {
        auto streamToVector(juce::InputStream &stream)
        {
            using namespace juce;
            std::vector<std::byte> result((size_t)stream.getTotalLength());
            stream.setPosition(0);
            [[maybe_unused]] const auto bytesRead = stream.read(result.data(), result.size());
            jassert(bytesRead == (ssize_t)result.size());
            return result;
        }

        const char *getMimeForExtension(const juce::String &extension)
        {
            using namespace juce;
            static const std::unordered_map<String, const char *> mimeMap =
                {
                    {{"htm"}, "text/html"},
                    {{"html"}, "text/html"},
                    {{"txt"}, "text/plain"},
                    {{"jpg"}, "image/jpeg"},
                    {{"jpeg"}, "image/jpeg"},
                    {{"svg"}, "image/svg+xml"},
                    {{"ico"}, "image/vnd.microsoft.icon"},
                    {{"json"}, "application/json"},
                    {{"png"}, "image/png"},
                    {{"css"}, "text/css"},
                    {{"map"}, "application/json"},
                    {{"js"}, "text/javascript"},
                    {{"woff2"}, "font/woff2"}};

            if (const auto it = mimeMap.find(extension.toLowerCase()); it != mimeMap.end())
                return it->second;

            jassertfalse;
            return "";
        }
    } // namespace

namespace {}

    //==============================================================================
    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p),
          webView{juce::WebBrowserComponent::Options{}
                      .withBackend(
                          juce::WebBrowserComponent::Options::Backend::webview2)
                      .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
                                                  .withUserDataFolder(juce::File::getSpecialLocation(
                                                      juce::File::tempDirectory))
                                                  .withBackgroundColour(juce::Colours::white))
                      .withResourceProvider([this](const auto &url)
                                            { return getResource(url); })
                        .withNativeIntegrationEnabled()}
    {
        juce::ignoreUnused(processorRef);

        addAndMakeVisible(webView);

        // webView.goToURL("https://juce.com");
        webView.goToURL(webView.getResourceProviderRoot());

        setResizable(true, true);
        setSize(800, 600);
    }

    AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
    {
    }

    void AudioPluginAudioProcessorEditor::resized()
    {
        // This way the webView fills the entire bounds of the window.
        webView.setBounds(getLocalBounds());
    }

    auto AudioPluginAudioProcessorEditor::getResource(const juce::String &url) -> std::optional<Resource>
    {
        std::cout << url << std::endl;

        static const auto resourceFileRoot = juce::File{R"(/Users/kaimueller/Documents/Development/juce-projects/webview-plugin/plugin/ui/public)"};

        // Relative path
        const auto resourceToRetrieve = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);

        const auto resource = resourceFileRoot.getChildFile(resourceToRetrieve).createInputStream();

        if (resource)
        {
            const auto extension = resourceToRetrieve.fromFirstOccurrenceOf(".", false, false);
            return Resource{streamToVector(*resource), getMimeForExtension(extension)};
        }

        return std::nullopt;
    }
} // namespace webview_plugin