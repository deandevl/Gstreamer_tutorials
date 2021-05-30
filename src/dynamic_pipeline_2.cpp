//
// Created by Rick on 2021-03-06.
//
#include <gst/gst.h>

// Structure to contain all our information , so we can pass it to callback
typedef struct _CustomData {
  GstElement *pipeline;
  GstElement *source;
  GstElement *audio_convert;
  GstElement *video_convert;
  GstElement *audio_resample;
  GstElement *audio_sink;
  GstElement *video_sink;
} CustomData;

// Handler for the pad-added signal
static void pad_added_handler(GstElement *src, GstPad *pad, CustomData *data);

int main(int argc, char *argv[]) {
  CustomData data;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  gboolean terminate = FALSE;

  // Initialize GStreamer
  gst_init(&argc, &argv);

  // Create the elements
  data.source = gst_element_factory_make("uridecodebin", "source");

  data.audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
  data.video_convert = gst_element_factory_make("videoconvert", "video_convert");

  data.audio_resample = gst_element_factory_make("audioresample", "audio_resample");

  data.audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");
  data.video_sink = gst_element_factory_make("autovideosink", "video_sink");

  // Create the empty pipeline
  data.pipeline = gst_pipeline_new("test-pipeline");

  if(!data.pipeline || !data.source){
    g_printerr("Pipeline or source elements could not be created \n");
    return -1;
  }

  if(!data.audio_convert || !data.audio_resample || !data.audio_sink){
    g_printerr("Not all audio elements could be created \n");
    return -1;
  }

  if(!data.video_convert || !data.video_sink){
    g_printerr("Not all video elements could be created \n");
    return -1;
  }

  // Build the pipeline. Note that we are NOT linking the source at this point.
  // We will do it later.
  gst_bin_add_many(
      GST_BIN(data.pipeline),
      data.source,
      data.audio_convert,
      data.video_convert,
      data.audio_resample,
      data.audio_sink,
      data.video_sink,
      nullptr);
  if(!gst_element_link_many(
      data.audio_convert,
      data.video_convert,
      data.audio_resample,
      data.audio_sink,
      data.video_sink,
      nullptr)){
    g_printerr("Elements could not be linked.\n");
    gst_object_unref(data.pipeline);
    return -1;
  }

}
