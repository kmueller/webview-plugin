# Version is needed by JUCE.
project(Juce8WebViewPlugin VERSION 0.1.0)

juce_add_plugin(Juce8WebViewPlugin
    COMPANY_NAME YourCompany
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE YCMC
    PLUGIN_CODE J8WP
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Juce8WebViewPlugin"

    # NEEDS_WEB_BROWSER TRUE
    NEEDS_WEBVIEW2 TRUE
)

target_sources(Juce8WebViewPlugin
    PRIVATE source/PluginEditor.cpp source/PluginProcessor.cpp
)

target_include_directories(Juce8WebViewPlugin PRIVATE include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        # This will enable WebView2 as the WebView backend on Windows
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
)

# Folder where web UI data reside
set(WEBVIEW_FILES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui/public")

# Copy JUCE frontend library to plugin UI files
file(COPY "${JUCE_MODULES_DIR}/juce_gui_extra/native/javascript/" DESTINATION "${WEBVIEW_FILES_SOURCE_DIR}/js/juce/")

add_compile_definitions(JUCE_DEBUG=1)