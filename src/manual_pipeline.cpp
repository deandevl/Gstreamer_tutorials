//
// Created by Rick on 2021-02-07.
//
#include <gst/gst.h>

int main(int argc, char *argv[]){
  GstElement *pipeline, *source, *sink, *filter, *converter;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;

  //  Initialize GStreamer
  gst_init(&argc, &argv);

  // Create the elements
  source = gst_element_factory_make("videotestsrc", "source");
  filter = gst_element_factory_make("vertigotv", "filter");
  converter = gst_element_factory_make("videoconvert", "converter");
  sink = gst_element_factory_make("autovideosink","sink");

  // Create the empty pipeline
  pipeline = gst_pipeline_new("test-pipeline");

  if(!pipeline || !source || !filter || !converter || !sink){
    g_printerr("Not all elements could be created.\n");
    return -1;
  }

  // Build the pipeline
  gst_bin_add_many(GST_BIN(pipeline), source, filter, converter, sink, nullptr);
  //if(gst_element_link(source, sink) != TRUE){
  if(gst_element_link_many(source, filter, converter, sink, nullptr) != TRUE){
    g_printerr("Elements could not be linked.\n");
    gst_object_unref(pipeline);
    return -1;
  }

  // Modify the source's properties
  // 0 = color bars; 18 = moving ball; 21 = pinwheel
  //g_object_set(source, "pattern", 0, nullptr);
  g_object_set(source, "pattern", 18, nullptr);

  // Start playing
  ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
  if(ret == GST_STATE_CHANGE_FAILURE){
    g_printerr("Unable to set the pipeline to the playing state.\n");
    gst_object_unref(pipeline);
    return -1;
  }

  //Wait until error or end of EOS
  bus = gst_element_get_bus(pipeline);
  msg = gst_bus_timed_pop_filtered(bus,
          GST_CLOCK_TIME_NONE,
    static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

  // Parse message
  if(msg != nullptr){
    GError *err;
    gchar *debug_info;

    switch (GST_MESSAGE_TYPE(msg)) {
      case GST_MESSAGE_ERROR:
        gst_message_parse_error(msg, &err, &debug_info);
        g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
        g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error(&err);
        g_free(debug_info);
        break;
      case GST_MESSAGE_EOS:
        g_print("End of stream reached.\n");
        break;
      default:
        // We could not reach here because we only asked for ERRORS and EOS
        g_printerr("Unexpected message received.\n");
        break;

    }

    // Free resources
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
  }

}
