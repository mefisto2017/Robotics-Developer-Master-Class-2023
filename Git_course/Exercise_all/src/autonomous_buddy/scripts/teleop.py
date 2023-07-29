#!/usr/bin/env python

from __future__ import print_function

import rospy
from geometry_msgs.msg import Twist
import sys, select, termios, tty

msg = """
Reading from keyboard
---------------------------
Use the following keys to move the robot.
   w
a  s  d

SPACE key to stop

ESC key to quit
"""

linear_ = 0.
angular_ = 0.
l_scale_ = 0.5
a_scale_ = 0.5
dirty = False

KEYCODE_R = 'd' 
KEYCODE_L = 'a'
KEYCODE_U = 'w'
KEYCODE_D = 's'

bindings = {
    KEYCODE_L:(0.0, 1.0, True),
    KEYCODE_R:(0.0, -1.0, True),
    KEYCODE_U:(1.0, 0.0, True),
    KEYCODE_D:(-1.0, 0.0, True)
}

def getKey():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    # read 1 byte from STDIN
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)

    pub = rospy.Publisher('cmd_vel', Twist, queue_size = 1)
    rospy.init_node('teleop') 

    try:
        print(msg)
        run = True
        while(run):
            key = getKey()
            linear_ = 0.
            angular = 0.
            dirty = False

            if(key == ' '):
                # if the SPACEBAR is pressed the velocity is set to 0 regardless of anything else
                linear_ = 0.
                angular_ = 0.
                dirty = True

            if key in bindings.keys():
                linear_ = bindings[key][0]
                angular_ = bindings[key][1]
                dirty = bindings[key][2]
            #ESC key
            elif ord(key) == 27: 
                print('quit')
                run = False
                continue

            twist = Twist()
            twist.linear.x = l_scale_*linear_
            twist.linear.y = 0;
            twist.linear.z = 0;
            twist.angular.x = 0;
            twist.angular.y = 0;
            twist.angular.z = a_scale_*angular_
            if dirty is True:
                pub.publish(twist)    
                termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
                dirty = False
            
           
    except Exception as e:
        print(e)