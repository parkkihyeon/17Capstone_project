2017 capstone project


-Abstract-

We propose software development which is projected to provide an AI Korean chess software by applying reinforcement learning from inputting online pro chess players¡¯ records and modifying MCTS algorithm. 

The goal of developing this software is to bring the best performance by applying algorithm with a constrained cpu. 

By the time this project is finished, we aim to bring the winning rate higher than 50% when playing with current online Korean chess software.



-Current Problem-

Our goal is making Korean Chess AI Program.
we tried to make a grpah with node and node is one histroy in one game.
And we made it.

But, problem is when we serialize this object(grpah) to text file.
The Error occured, called 'stack overflow'.

we estimate problem occured when we serialize inner object in graph.
inner object, called State_node,werializing member pointer 'next' and 'prev'
return error that we mentioned before.

we tried to find out what is problem. But, we couldn't find it.

Can someone help us? or can someone tell us what is problem?

Please!