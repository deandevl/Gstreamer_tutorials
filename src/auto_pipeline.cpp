//
// Created by Rick on 2021-02-03.
//

#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline;
  GstBus  *bus;
  GstMessage *msg;

  //  Initialize GStreamer
  gst_init(&argc, &argv);

  /* Build the pipeline */
  pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",
                              nullptr);
  /* Start playing */
  gst_element_set_state(pipeline, GST_STATE_PLAYING);

  /* Wait for error or end of stream */
  bus = gst_element_get_bus(pipeline);
  msg = gst_bus_timed_pop_filtered(bus,
          GST_CLOCK_TIME_NONE,
    static_cast<GstMessageType>(GST_MESSAGE_EOS | GST_MESSAGE_ERROR));

  /* Free resources */
  if(msg != nullptr){
    gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
  }

  return 0;
}
