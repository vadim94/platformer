#include "SDL_events.h"
#include "SDL_main.h"
#include "SDL.h"

#include "core/oxygine.h"

#include "Stage.h"
#include "DebugActor.h"
#include "ColorRectSprite.h"
#include "KeyEvent.h"

#include "GreySquareActor.h"

using namespace oxygine;

spActor createAndSetupActor()
{

   spGreySquareActor actor = new GreySquareActor(PhysicalObject::Point{50 * pixel, 50 * pixel});
   getStage()->addEventListener(KeyEvent::KEY_DOWN, [actor](Event* event)
   {
      const PhysicalObject::AccelerationVector horizontalAcceleration{ 500 * pixelPerSquareSecond , Acceleration(0) };
      KeyEvent* keyEvent = dynamic_cast<KeyEvent*>(event);
      if (!keyEvent) return;


      switch (keyEvent->data->keysym.scancode)
      {
      case SDL_SCANCODE_LEFT:
         actor->SetAcceleration(actor->GetAcceleration() - horizontalAcceleration);
         break;
      case SDL_SCANCODE_RIGHT:
         actor->SetAcceleration(actor->GetAcceleration() + horizontalAcceleration);
         break;
      case SDL_SCANCODE_SPACE:
         actor->Jump();
         break;
      }
   });
   return actor;
}

int mainloop()
{
   PhysicalObject().GetLocation();
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

   getStage()->addChild(createAndSetupActor());

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