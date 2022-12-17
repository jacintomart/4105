
***********************************   DISCLAIMER   ***********************************

The code in BinaryClassifier.ipynb and 10ClassClassifier.ipynb were sourced for project
research purposes ONLY. We do not claim any form of ownership or credit for the code in 
these files and all necessary references can be found below as well as in ProjectReport.txt


Project Summary
	The exploration of models and research into more complex algorithms such as convolutional 
  networks and audio and image classifiers utilizing such methods are of interest to the team. 
  The scope of applications is large with these models and thus implementation of them would 
  be of great advantage to the group. Specifically, the team is concerned with audio detection 
  models geared toward detecting and identifying gunshots in various environments. The 
  implementation of such a system could aid in community safety, security integrations, and 
  response systems. Through research and implementation of such a system the team aims to establish
  familiarity with the intricacies of said model while providing a net positive into the community.
  With the recent shootings occurring across the country, a working model may be used in schools, 
  government buildings, and other public areas to negate the harmful impacts that these events bring.
  Designing such a model also presents the opportunity for integration with larger systems, such as 
  triggering notifications or hardware that locks down classrooms/doors.
 
 
 
Project Details:
The dataset that will be used is the ‘UrbanSound’’ dataset found at the following link: 

  https://urbansounddataset.weebly.com/urbansound.html
  
The dataset includes 1302 labeled, 4 second, urban sound files split into ten classes: 

air_conditioner, car_horn, children_playing, dog_bark, drilling, engine_idling, gun_shot, jackhammer, siren, and street_music

In addition the audio files are randomized and split into ten folders, or “Folds”. It is 
made in such a manner so that a 10K fold cross validation can be performed. The dataset
also provides a .csv file listing all the audio files and their information, such as the 
class they belong to. 

In this project we hope to reprocess the data set to two classes, gunshots and not gunshots. 
Various preprocessing will be needed when doing so, especially when rearranging the data into 
two classes, the number of samples in each class will not be balanced (over/undersampling). 
A neural network algorithm will be built and trained using the new dataset in order to classify 
data input. Evaluation will be done by reporting the accuracies and losses of different training
practices used. Different types of preprocessing, training, and validation will be used to and 
analyzed for a comparison of the results.



Projection on Achievable Outcomes:
	The primary project outcome is aimed at the development of a working model capable of identifying 
  if an audio is indeed a gunshot or not. Iterative training will ensure acceptable accuracy of the 
  final model, where an audio input will be all that is necessary to classify new data.
