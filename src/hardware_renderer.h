#ifndef CMU462_HARDWARE_RENDERER_H
#define CMU462_HARDWARE_RENDERER_H

#include <stdio.h>

#include "CMU462.h"
#include "svg_renderer.h"

namespace CMU462 {

class HardwareRenderer : public SVGRenderer {
 public:

  HardwareRenderer();

  // implements Renderer
  ~HardwareRenderer() { }

  // draw an svg input to render target
  void draw_svg( SVG& svg );
    
  void rasterizePoint(float x, float y, Color color);

  void rasterizeLine(float x0, float y0,
                     float x1, float y1, 
                     Color color);

  void rasterizeTriangle(float x0, float y0,
                         float x1, float y1, 
                         float x2, float y2, 
                         Color color); 

  void rasterizeImage(float x0, float y0,
                      float x1, float y1,
                      Sampler2D* sampler,
                      Texture& tex);
    
}; // class HardwareRenderer

} // namespace CMU462

#endif // CMU462_HARDWARE_RENDERER_H
