#include "Juce8WebViewPlugin/PluginProcessor.h"
#include "Juce8WebViewPlugin/PluginEditor.h"

namespace webview_plugin
{
    //==============================================================================
    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p),
        webView{juce::WebBrowserComponent::Options{}.withBackend(
            juce::WebBrowserComponent::Options::Backend::webview2)
            .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder
            (juce::File::getSpecialLocation(juce::File::tempDirectory)))}
    {
        juce::ignoreUnused(processorRef);

        addAndMakeVisible(webView);

        webView.goToURL("https://juce.com");

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
}