Project 2: MDP

The figure (Fig. 17.1 from the book) visualizes the problem. The agent starts in the lower left 
corner of the environment, and needs to choose an action at each time step to navigate the environment. 
Navigation is terminated when the agent reaches one of the terminal states, which are the states with a 
+1 and -1 reward.

The actions available to the agent are [Up, Down, Left, Right], and they attempt to move the agent in 
that specific direction. There is a 0.8 probability that the agent will move in the direction of the 
chosen action. There is a 0.1 probability that the agent will move in one of two directions that is 
perpendicular to the desired direction, for each perpendicular direction.

The gray cell is an obstacle cell. If the agent bumps into a wall or the obstacle cell, then it stays 
in its current position.

Specifically, you need to implement a function called “valueIteration” that takes in the following parameters:
- A set of states
- A set of actions
- A transition model matrix
- A set of rewards
- A discount factor

You may use different parameters if you need/want to, but this is the minimum amount of information that the 
Value Iteration algorithm needs to perform. The function should return an array of utility values that 
represents the utility of each state.


You will be given a transition model matrix to use for this assignment in the mdp_transition_model.py file on 
Canvas. This transition model will be a 4x11x11 numpy array of floats. Pass this to your valueIteration function. 

Policy Computation
After finding the utilities for the problem, you should compute the policy. The value iteration algorithm returns 
a set of optimal utility values, but it doesn’t return the policy. The policy is obtained by determining the best 
action at each state, which will be the action with the highest expected utility.

Example Input/Output
Below are some examples of the utilities given rewards and discount factors. The utilities are printed in 
row-major order starting with the lower-left position.


Discount = 0.99 Reward = -0.04

Utilities: [ 0.65024905  0.59154444  0.55972331  0.33738693  0.71657452  0.6413271  -1.  0.77616784  
             0.84393469  0.90509581  1.        ]

Policy:

['R', 'R', 'R', 'T']

['U', '0', 'U', 'T']

['U', 'L', 'U', 'L']



Discount = 0.5 Reward = -0.04

Utilities: [-0.063318   -0.053526   -0.0199436  -0.0742348  -0.0412844   0.06626728
            -1.          0.0083588   0.1254934   0.3824285   1.        ]

Policy:

['R', 'R', 'R', 'T']

['U', '0', 'U', 'T']

['U', 'R', 'U', 'D']



Discount = 0.5 Reward = -0.25

Utilities: [-0.4741935  -0.4544055  -0.39861612 -0.48307075 -0.4450115  -0.25495483
            -1.         -0.3764725  -0.21356263  0.14447684  1.        ]

Policy:

['R', 'R', 'R', 'T']

['U', '0', 'U', 'T']

['U', 'R', 'U', 'L']
