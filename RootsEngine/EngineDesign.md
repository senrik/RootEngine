# Roots Engine Documentation

## Structure

### Core (Memory Management)

Using a 64-bit architecture as a base. We will be creating pools of memory with in a specifies max size to have a resource pool. We should make this modular so that when we increase the max memory size it is. We need to create exceptions and cases that will cause the system to recover if there is a fault.

We also will have to have a means of serializing visual data, consistent with Vulkan. 

### Input

Takes unbuffered input from the keyboard, mouse, and a controller if there is one connected. This is then mapped to a data structure that models all the input devices. We will want to create a layer of abstraction above this that allows for specific input to be tied to any in-game action (re-binding keys).

### Audio

Plays audio files based of off triggers, with controls that allow for simple modifications (pitching and croping clips).

### Graphics Pipeline

Receive data from the core to display objects to the user. We will need to serialize position, rotation, and scale of the objects. Objects will also

### Physics

Look into getting a free physics library and implementing it fully into the engine.

### Game Logic 

Quests, events, AI agents, triggers.

## Milestones

### Milestone 1 - Text-based RPG

Create a text based RPG with six rooms, text commands to explore, talk to an NPC, and attack.

OOP implementation the the game logic