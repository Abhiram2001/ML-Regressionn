#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define numTraininginputs 506
#define totalInput 506

double learningRate = 0.01;
double input[totalInput][14];
double actualOutput[totalInput];
double correctAnswer[totalInput];
double variables[14];
double variation[14];
double max[14];

void getInputdata()
{
    FILE *file = fopen("Housing.csv","r");
    
    for(int i=0;i<totalInput;i++)
    {
        fscanf(file,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&input[i][0],&input[i][1],&input[i][2],&input[i][3],&input[i][4],&input[i][5],&input[i][6],&input[i][7],&input[i][8],&input[i][9],&input[i][10],&input[i][11],&input[i][12],&correctAnswer[i]);
        input[i][13]=1;
    }
    fclose(file);
    for(int j=0; j<13;j++)
    {
        for(int i =0; i<totalInput;i++)
        {
            if(max[j]<input[i][j])
                max[j] = input[i][j];
        }
        for(int i =0; i<totalInput;i++)
        {
            input[i][j]/=max[j];
        }
    }
    for(int i =0; i<totalInput;i++)
    {
        if(max[13]<correctAnswer[i])
            max[13] = correctAnswer[i];
    }

    for(int i =0; i<totalInput;i++)
    {
        correctAnswer[i]/=max[13];
    }
}

void initialize()
{
    for(int i = 0; i<13 ;i++)
    {
        float temp = rand()%100;
        temp/=99;
        variables[i] = temp;
    }
    variables[13]=0;
}

void forward()
{
    int j = 0;
    for(int i = 0;i<numTraininginputs; i++)
    {
        double curr = 0.0;
        for (j=0;j<14;j++)
        {
            curr += (input[i][j] * variables[j]);
        }
        actualOutput[i] = curr;
    }
}

double loss()
{
    double loss,change,sum = 0.00;
    for (int i =0; i<numTraininginputs;i++)
    {
        change = (correctAnswer[i]-actualOutput[i]);
        sum = sum+(change*change);
    }
    loss = sum/numTraininginputs;
    return loss;
}

void backward()
{
    double loss,change,sum = 0.00;
    for(int j=0; j<14;j++)
    {
        double temp =0.0;
        sum = 0.0;
       for(int i=0;i<numTraininginputs;i++)
       {
           change = (correctAnswer[i]-actualOutput[i])*input[i][j];
           sum += change;   
       }
       temp = ((2.00/numTraininginputs)*sum);
       variation[j] = temp;
    }

    for(int i=0;i<14;i++)
    {
        variables[i] = (variables[i] + (variation[i] * learningRate));
    }
}

void training()
{
    for(int i= 0; i<10000; i++)
    {
        double temp;
        forward();
        backward();
        if(i%1000 == 0)
        {
            temp = loss();
            printf("loss is  %lf \n",temp);
        }
    }
}
int main()
{
    getInputdata();
    initialize();
    training();
    forward();
    printf("Predicted output ----Actual output \n");
    for(int i=0;i<numTraininginputs;i++)
    {
        printf("%lf----------- %lf\n",(actualOutput[i]*max[13]),(correctAnswer[i]*max[13]));
    }
}