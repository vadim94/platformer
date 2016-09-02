#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"


using namespace oxygine;

int mainloop()
{
   bool done = core::update();

   getStage()->update();

   if (core::beginRendering())
   {
      Color clearColor(32, 32, 32, 255);
      Rect viewport(Point(0, 0), core::getDisplaySize());
      getStage()->render(clearColor, viewport);

      core::swapDisplayBuffers();
   }

   return done ? 1 : 0;
}

// Application entry point
void run()
{
   ObjectBase::__startTracingLeaks();

   core::init_desc desc;
   desc.title = "Oxygine Application";

   desc.w = 960;
   desc.h = 640;

   core::init(&desc);


   Stage::instance = new Stage(true);
   Point size = core::getDisplaySize();
   getStage()->setSize(size);

   DebugActor::show();

   // This is the main game loop.
   while (1)
   {
      int done = mainloop();
      if (done)
         break;
   }
   ObjectBase::dumpCreatedObjects();

   core::release();
   ObjectBase::dumpCreatedObjects();

   ObjectBase::__stopTracingLeaks();
   //end
}


#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
   void one(void* param) { mainloop(); }
   void oneEmsc() { mainloop(); }

   int main(int argc, char* argv[])
   {

      run();
      return 0;
   }
};
#endif