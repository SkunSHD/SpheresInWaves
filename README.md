# Spheres In Waves

### It's a first player shooter game where spheres are spawned in waves and there is an ability to destroy spheres just by shooting at them.

### Game mechanics:

#### The first wave:
- 15 spheres are spawned:
	- 10 within a 1500 radius (close radius)
	- 5 within a 2000 radius (far radius)
- spawn center is player's location.

#### Next wave:
- the amount of spheres increses by 10%
- radius increses by 5%
- spawn center is player's location at the end of the previous wave

#### Wave is finished:
- when 10 spheres within the close radius are destroyed

#### Spheres spawning features:
- random location
- minimum distance between spheres is 80
- keep an ability to end a wave (10 spheres within the close radius)

#### Other Game Features:
- Blueprints are used but only a bit (WaveScoreWidget). The most part of the game's logic is written in C++
- All settings are blueprint editable (min radius, number of spheres to spawn, etc.)
- UI for the wave number and the amount of destroyed spheres
- Each new sphere is decreased in size by editable value and there is a minimum size fot it
- Debug Drawings which can be enabled in game mode settings (allow to see min/max radius, sphere offset)