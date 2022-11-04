In this homework, we will use the cancer dataset. (Note: You can use the built-
in function from ML libraries for gradient descent, training, and validation.) 
Also, sample code for accessing and cleaning up the dataset provided in 
Canvas. For the evaluation of this homework across all problems, use 80%, 
20% split. We will also use US Housing dataset with  80% and 20% split
between training and evaluation (test) sets.

Problem 1 (50pts):

Use the cancer dataset to build an SVM classifier to classify the type of cancer 
(Malignant vs. benign). Use the PCA feature extraction for your training. 
Perform N number of independent training (N=1, …, K).

Identify the optimum number of K, principal components that achieve the highest classification accuracy. 
Plot your classification accuracy, precision, and recall over a different number of Ks. 
Explore different kernel tricks to capture non-linearities within your data. 
Plot the results and compare the accuracies for different kernels.
Compare your results against the logistic regression that you have done in homework 3.
Make sure to explain and elaborate your results.

 

Problem 2 (50pts):

Develop a SVR regression model that predicts housing price based on the 
following input variables:

Area, bedrooms, bathrooms, stories, mainroad, guestroom, basement,
hotwaterheating, airconditioning, parking, prefarea

Compare your results against linear regression with regularization loss that 
you already did in homework1. 
Use the PCA feature extraction for your training. Perform N number of 
independent training (N=1, …, K). Identify the optimum number of K, 
principal components that achieve the highest regression accuracy. 
Explore different kernel tricks to capture non-linearities within your data.
Plot the results and compare the accuracies for different kernels.
