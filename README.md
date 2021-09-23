# Balls In Waves

### It's a first player shooter game where spheres are spawned in waves and there is an ability to destroy spheres just them by shooting at them.

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
- Blueprints are used for WaveScoreWidget though the most part of the game logic is written in C++
- All settings are blueprint editable
- UI for wave score and amount of destroyed spheres
- Each new sphere is decreased in size by editable value and there is a minimum size