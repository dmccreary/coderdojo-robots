Our next lab is a collision avoidence program.  This program has the robot
driving forward unless the robot senses an object in front of it.  If the
object is less then the threshold for turn (cm_for_turn) then the robot
will change the direction of one wheel and turn right.

```C
if (dist_in_cm < cm_for_turn) {
      turn_right();
    } else {
      move_forward();
    }
```

{{site_url}}
[Source code]
../../src/collision-avoidance-ping/collision-avoidance-no-leds/collision-avoidance-no-leds/collision-avoidance-no-leds.ino