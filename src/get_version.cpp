#include <iostream>
#include <gst/gst.h>

int main(int argc, char *argv[]) {
  const gchar *nano_str;
  guint major = 0, minor = 0, micro = 0, nano = 0;

  gst_init(&argc, &argv);
  gst_version(&major, &minor, &micro, &nano);

  if(nano == 1) nano_str = "(CVS)";
  else if(nano == 2) nano_str = "(Prerelease)";
  else nano_str = "";

  printf("This program is linked against GStreamer %d.%d.%d %s\n", major,minor,micro, nano_str);

  /*std::cout << "Hello, World!" << std::endl;*/

  return 0;
}
