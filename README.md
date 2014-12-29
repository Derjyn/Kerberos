# Kerberos Engine 
_Version 0.0.1.5 (Conceptus)_ 

---

#### Changelog  
_12/29/2014_
  + Major overhaul of code
  + Most systems (6/9) current systems running
  + Lab (demo) added
  
#### Roadmap
  + Implement scripting system
  + Implement AI system
  + Implement networking system
  + Move to component based entities
  + Implement state system  
---
  
## Introduction  

The Kerberos engine is currently a playground of sorts to test out various
functionality and features for interactive media (ie, games) applications. As functionality is tested and code cleaned up, it is added to the engine. While there is a clear vision for the types of applications created with Kerberos, effort is being made to keep things as open as possible to allow for the engine to be modified and expanded upon to enable different styles and types of applications to be built using Kerberos.

Please note that in it's current state, Kerberos code is messy and not exactly the most advanced.  Still, it is functional and pretty. At the very least, one could browse through the code and pick up a few useful snippets, or see how the various different systems get along. Here is a current (as of version 0.0.1.5) list of the various 3rd party fun-bits worked into Kerberos:

 + Ogre3D
 + Bullet / BtOgre
 + FMOD
 + Particle Universe
 + Gorilla
 + Ook
 
There are future plans to implement Berkelium or libRocket for more interactive GUI functionality. Testing was done with PhysX and Bullet, and while PhysX is pretty slick, it fell behind in several performance test and added on a huge amount of work when it comes to shipping an application. There are several other 3rd party libraries that may get worked in, but the next several sprints for Kerberos will be dedicated to tightening some screws and cleaning up semantics and design choices.

---

## Building

TODO - cover the dependencies and build system setup.

---

## Usage

TODO - Not a lot to use yet... Just grab the code and do the things!

---

## Credits