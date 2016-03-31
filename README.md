# Bade3D

**Actually under development, help appreciated, there is really much stuff to do for a little engine**

This want to be a really simple rendering engine providing certain cutting-edge features while at same time
without adding typical boiler plate code:

**Features:**
* Threaded Rendering
* States Minimization
* Managed resources
* Simple interface


**Minimalism:**
* Bade3D DON'T have a scene graph
* Bade3D DON'T have a math library
* Bade3D DON'T do any kind of sorting behind the scenes
* Bade3D DON'T don't create windows nor OpenGL context


## Threaded rendering

Bade3D is thinked to be used from 2 threads:

**Rendering Thread:**
All OpenGL calls are deferred to be executed in another thread, 
this gives the main thread the chance to perform states optimization
without impacting rendering performance.

All you have to do is setup a OpenGL context in a thread, call `renderer->render();` from there
and of course you have to swap buffers.

**Main Thread:**
Just create a RenderList and let the engine optimize the stuff in the list for you.

`queue->compileStates(renderList);`

See documentation to learn building the renderlist (really simple, just a bunch of classes)

## Dependency Injection

Bade3D uses a [Dependency Injection Framework](https://github.com/Darelbi/Infectorpp2),
you are not forced to use it and you can still use Bade3D like an advanced IVideoDriver 
(if you ever used Irrlicht, you know what I mean).
If you ever used Ninject or Svelto frameworks instead you can unleash your knowledge of advanced programming
patterns to Inject components of the engine in your code, even better you have already
a Dependency Injection framework for C++.




**Original author**: [Darelbi](https://github.com/Darelbi)

**Contributors**:  list empty 
