#include<iostream>
#include<vector>
using namespace std;

void multiply(vector<vector<float>> &inp, vector<vector<float>> &sc, vector<vector<float>> &out, int v){

    for(int i=0; i<2; i++){
        for(int j=0; j<v; j++){
            for(int k=0; k<2; k++){
                out[i][j] += sc[i][k] * inp[k][j];
            }
        }
    }
    out[0][v] = out[0][0];
    out[1][v] = out[1][0];
}

int main(){
    vector<vector<float>> input(2, vector<float>(10,0));
    vector<vector<float>> scale(2, vector<float>(2,0));
    vector<vector<float>> output(2, vector<float>(10,0));
    int v;
    float sx,sy;

    cout<<"Enter no. of Vertex :";
    cin>>v;

    for(int i=0; i<v; i++){
        cout<<"\nEnter X :";
        cin>>input[0][i];
        cout<<"Enter Y :";
        cin>>input[1][i];

        //input[i][2]=1;
    }
    cout<<"\nInput matrix :\n";
    for(int j=0; j<2; j++){
        for(int k=0; k<v; k++){
               cout<<input[j][k]<<" ";
        }
        cout<<"\n";
    }

    cout<<"\nEnter Sx :";
    cin>>sx;
    cout<<"\nEnter Sx :";
    cin>>sy;

    scale = {{sx,0},{0,sy}};
    cout<<"\nScaling matrix :\n";
    for(int j=0; j<2; j++){
        for(int k=0; k<v; k++){
               cout<<scale[j][k]<<" ";
        }
        cout<<"\n";
    }

    multiply(input, scale, output, v);

    cout<<"Result matrix :\n";
    for(int j=0; j<2; j++){
        for(int k=0; k<v; k++){
               cout<<output[j][k]<<" ";
        }
        cout<<"\n";
    }
    

    return 0;
}