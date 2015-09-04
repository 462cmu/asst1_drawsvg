#ifndef CMU462_RENDERER_H
#define CMU462_RENDERER_H

#include <stdio.h>
#include <string>

namespace CMU462 {

/**
 * Abstract renderer definition.
 * The abstract class defines a general framework for user-space renderers.
 * User space renderers can have different routines for drawing, and the 
 * viewer will call the render function to display the output of user space 
 * renderers. The viewer will also forward events such as buffer resizes to 
 * the user space renderer for it to respond. It will also pass events that it 
 * does not know how to handle to the renderer so that the renderer can define
 * its own control keybindings, etc. 
 */
class Renderer {
 public:

  /**
   * Virtual Destructor.
   * Each renderer implementation should define its own destructor 
   * that takes care of freeing the resources that it uses. 
   */
  virtual ~Renderer( void ) { }

  /**
   * Initialize the renderer.
   * A renderer may have some initialization work to do before it is ready
   * to be used. The viewer will call the init function before using the 
   * renderer in drawing. 
   */
  virtual void init( void ) = 0;

  /**
   * Draw content.
   * Renderers are free to define their own routines for drawing to the 
   * context. The viewer calls this function on every frame update.
   */
  virtual void render( void ) = 0;

  /**
   * Respond to buffer resize.
   * The viewer will inform the renderer of a context resize by calling
   * this function. The renderer has complete freedom to handle resizing,
   * and a good renderer implementation should handle resizes properly. 
   * \param w The new width of the context
   * \param h The new height of the context
   */
  virtual void resize( size_t w, size_t h ) = 0;

 /**
   * Return a name for the renderer.
   * If the viewer has a renderer set at initialization, it will include 
   * the renderer name in the window title.
   */
  virtual std::string name( void ) = 0;

  /**
   * Return a brief description of the renderer.
   * Each renderer can define this differently. The viewer will use the 
   * returned value in the renderer section of its on-screen display.
   */
  virtual std::string info( void ) = 0;

  /**
   * Respond to key event.
   * Renderers are allowed to define their own control keybindings for
   * user interaction but will only do this through the viewer. The viewer 
   * will try to handle all the window events and will inform the renderer
   * of events that it does not care about. Therefore renderers should avoid
   * using keybindings that the viewer already uses. (see Viewer for details)
   * \param key The key being pressed by the user.
   */
  virtual void key_event( char key ) = 0;

  /**
   * Respond to cursor events.
   * The viewer itself does not really care about the cursor but it will take 
   * the GLFW cursor events and forward the ones that matter to  the renderer. 
   * The arguments are defined in screen space coordinates.
   * \param x the x coordinate of the cursor
   * \param y the y coordinate of the cursor
   * \param keys encodes the current mouse buttons state in a bitmask
   *             each bit from the least significant to the most significant
   *             encodes: right mouse button, middle mouse button, left mouse 
   *             button.
   */
  virtual void cursor_event( float x, float y, unsigned char keys ) = 0;

  /**
   * Respond to zoom event.
   * Like cursor events, the viewer itself does not care about the mouse wheel 
   * either, but it will take the GLFW wheel events and forward them directly 
   * to the renderer. 
   * \param offset_x scroll offset in x direction
   * \param offset_y scroll offset in y direction
   */
  virtual void scroll_event( float offset_x, float offset_y ) = 0;

};

} // namespace CMU462

#endif // CMU462_RENDERER_H
