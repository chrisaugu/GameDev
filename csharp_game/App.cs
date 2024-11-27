// using System;
using Microsoft.Xna.Framework;

namespace Blocks
{
    class App : Game
    {
        private readonly GraphicsDeviceManager graphics;
        
        public App()
        {
            graphics = new GraphicsDeviceManager(this);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.DimGray);
        }

        public static void Main()
        {
            using var app = new App();
            app.Run();
        }
    }
}