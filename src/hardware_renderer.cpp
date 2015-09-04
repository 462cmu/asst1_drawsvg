#include "hardware_renderer.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace CMU462 {

HardwareRasterizer::HardwareRasterizer() { }


void HardwareRasterizer::rasterizePoint(float x, float y, Color color) {
  
  glBegin( GL_POINTS );
  glColor3f(color.r, color.g, color.b);
  glVertex2f( x + 0.5, y + 0.5 );
  glEnd();

}

void HardwareRasterizer::rasterizeLine(float x0, float y0,
                                       float x1, float y1, 
                                       Color color) {

  glBegin( GL_LINES );
  glColor3f(color.r, color.g, color.b);
  glVertex2f( x0 + 0.5, y0 + 0.5 );
  glVertex2f( x1 + 0.5, y1 + 0.5 );
  glEnd();

}

void HardwareRasterizer::rasterizeTriangle(float x0, float y0,
                                           float x1, float y1, 
                                           float x2, float y2, 
                                           Color color) {
  glBegin( GL_TRIANGLES );
  glColor3f(color.r, color.g, color.b);
  glVertex2f( x0 + 0.5, y0 + 0.5 );
  glVertex2f( x1 + 0.5, y1 + 0.5 );
  glVertex2f( x2 + 0.5, y2 + 0.5 );
  glEnd();

}

void HardwareRasterizer::rasterizeImage(float x0, float y0,
                                        float x1, float y1,
                                        Sampler2D* sampler,
                                        Texture& tex) {
  glColor4f(1, 1, 1, 1);

  // use mip level 0 and let opengl take care of its own mipmaping
  size_t w = tex.mipmap[0].width;
  size_t h = tex.mipmap[0].height;
  unsigned char* texels = &tex.mipmap[0].texels[0];

  GLuint texid;
  glGenTextures(1, &texid);

  glBindTexture(GL_TEXTURE_2D, texid);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
  
  // create texture and mipmap
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 
                              0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  // enable texture and draw
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 1.0); glVertex2f(x0, y1);
  glTexCoord2f(1.0, 1.0); glVertex2f(x1, y1);
  glTexCoord2f(1.0, 0.0); glVertex2f(x1, y0);
  glTexCoord2f(0.0, 0.0); glVertex2f(x0, y0);
  glEnd();

  glDisable(GL_TEXTURE_2D);

  return;
}

} // namespace CMU462

