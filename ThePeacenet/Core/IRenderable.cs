﻿using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThePeacenet.Core
{
    public interface IRenderable
    {
        void Update(GameTime gameTime);
        void Draw(GameTime gameTime);
    }
}