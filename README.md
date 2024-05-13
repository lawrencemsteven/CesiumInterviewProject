# Build Instructions:
```
cmake -B build
cmake --build build --config Release --target MountStHelens
```

# Notes:
This was completed within the three hour timespan and I am happy with the project for the most part except for `TerrainHeightmap::walk`. This function definitely
needed some more time as I only had around 45 minutes left to complete it.

One main issue that I am aware of is that the travel distance is not always correct. In other words the loop that walks along the surface does not end correctly.
I believe the check `horizontalDistTraveled <= abs(static_cast<double>(end.x) - static_cast<double>(start.x))` has some issues due to floating point comparison.
To do this correctly, I would have used my `containingBox` vector to instead stop once it reaches the intended vertex. There is definitely some more thinking involved
with that solution as the different directions of travel need to be considered. It would also have to ensure that the origin and given direction do not ever miss that endpoint.

That is the first thing I would fix. Here is a few other things that I would add given a larger allotted time:
- Doxygen comments for the function headers.
- Unit Tests
- Split up `TerrainHeightmap::walk` function as it is too complex for just one function.

Overall, I enjoyed the challenge and appreciate the opportunity, thank you!
