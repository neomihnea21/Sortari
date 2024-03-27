#include <fstream>
#include <iostream>
#include<cstring>
#include<queue>
#include<chrono>
#include<algorithm>
using namespace std;
///pentru simplitate, sa presupunem ca nu sunt chei negative
bool isSorted(vector<double> a, int n){
    for(int i=1; i<n; i++)
        if(a[i]<a[i-1])
          return false;
    return true;
}
void insertion(vector<double> &a, int n){
    if(n<20000){
        for(int i=1; i<n; i++){
            double key=a[i], j=i-1;
            while(j>=0&&a[j]>key){
                a[j+1]=a[j];
                j--;
            }
            a[j+1]=key;
        }
    }
    else cout<<"NU SE POATE FACE INSERTION SORT";
}
const int MAXR=1e8;
int ct[MAXR];
void countingSort(vector<int> &a, int n){
    for(int i=0; i<n; i++){
        if(a[i]!=(int)(a[i])){
            cout<<"NU SE POATE FACE COUNTING SORT, NU SUNT INTREGI\n";
            return;
        }
    }
    int lo=1e9, hi=-1;
    for(int i=0; i<n; i++){
        lo=min(lo, a[i]);
        hi=max(hi, a[i]);
    }///la counting, vectorul e automat normalizat
    if(hi-lo>1e8){
        cout<<"NU SE POATE FACE COUNTING SORT, SUNT PREA MARI\n";
        return;
    }
    memset(ct, 0, sizeof(ct[0])*(hi-lo+1));///trebuie initializat vectorul cu zerouri, cat trebuie
    for(int i=0; i<n; i++)
        ct[a[i]-lo]++;
    int index=0;
    for(int i=0; i<=hi-lo; i++){
        while(ct[i]>0){
            a[index]=i+lo;
            index++;
            ct[i]--;
        }
    }
}
void shellSort(vector<double> &a, int n){
   if(n<55000){
    vector<int> gaps;
    int start=1;
    while(start<n) start<<=1;
    start>>=2;
    while(start>0){
        gaps.push_back(start);
        start>>=1;
    }
    for(int k=0; k<gaps.size(); k++){
        for(int i=gaps[k]; i<n&&!isSorted(a, n); i++){
            int temp=a[i], j;
            for(j=i; j>=gaps[k]&&a[j-gaps[k]]>temp; j-=gaps[k])///facem o sortare prin insertie, doar ca pe sarite
                a[j]=a[j-gaps[k]];
            a[j]=temp;
        }
    }
   }
   else{
      cout<<"NU MERGE SHELLSORT\n";
   }
}
///mergesort
vector<double> L(1e8, 0);///sa fie gata alocat spatiul, resize-urile in recursie duc la 80% mai mult timp
void merging(vector<double> &a, int lo, int mid, int hi){
    int i=lo, j=mid+1, index=0;
    while((i<mid+1)&&(j<hi+1)){
        if(a[i]<a[j]){
            L[index]=a[i], index++, i++;
        }
        else{
            L[index]=a[j], index++, j++;
        }
        if(i==mid+1)
            while(j<hi+1)
              L[index]=a[j], index++, j++;
        if(j==hi+1)
            while(i<mid+1)
              L[index]=a[i], index++, i++;
    }
    for(int i=lo; i<=hi; i++)
        a[i]=L[i-lo];
}
void mergesort(vector<double> &a, int lo, int hi){///va fi nevoie de apeluri recursive
   if(lo<hi){///SE APELEAZA CU (a, 0, len-1)!!
      int mid=lo+(hi-lo)/2;
      mergesort(a, lo, mid);
      mergesort(a, mid+1, hi);
      merging(a, lo, mid, hi);
   }
}
///am mutat pivotarea de la qs inhouse, un call recursiv il incetineste ca vai de viata lui
void quicksort(vector<double> &a, int lo, int hi, int codPivot){///SE APELEAZA cu (a, 0, n-1) -sorteaza intre indicii lo si hi in vector, inclusiv
   if(lo<hi){
      if(codPivot==1)
         swap(a[(lo+hi)/2], a[hi]);
      int pivot=a[hi], j=lo-1;///ultimul e intotdeauna pivot, pentru alegeri diferite se va muta acolo, sa nu bag 2 pivotari
      for(int i=lo; i<=hi; i++){
         if(a[i]<pivot){
            j++;
            swap(a[i], a[j]);
         }
      }
      swap(a[j+1], a[hi]);
      quicksort(a, lo, j, codPivot);
      quicksort(a, j+2, hi, codPivot);
   }
}
void heapsort(vector<double> &a, int n){
    priority_queue<double> pq;
    for(int i=0; i<n; i++)
        pq.push(a[i]);
    for(int i=0; i<n; i++){
        a[n-i-1]=pq.top();
        pq.pop();
    }
}
void radixSort(vector<int> &a, int n, int base)
{
    queue<int> buc[256];///bucket-urile in care punem numerele in functie de cifra de pe pozitia j, vom lucra cu baza maxima 2^16
    int maxx=0,ct=0;
    for(int i=0;i<n;i++)
    {
        if(maxx<a[i])
        {
            maxx=a[i];
        }
    }
    while(maxx>0){
        maxx/=base;
        ct++;
    }
    int po=1;
    int cif;
    int it=0;
    for(int j=0; j<ct; j++){
        for(int i=0; i<n; i++){
            cif=(a[i]/po)%base;
            buc[cif].push(a[i]);
        }
        it=0;
        for(int i=0;i<base;i++){
            while(!buc[i].empty()){
                a[it]=buc[i].front();
                buc[i].pop();
                it++;
            }
        }
        po*=base;
    }
}
int main()
{
    vector<double> a;
    vector<int> aInt; ///vom tine 2 versiuni ale aceluiasi vector: cu double si cu int, pentru tipurile de sortari
    ifstream fin("siruri.txt");
    ofstream fout("results.out");
    int n; fin>>n;
    bool suntIntregi=true;
    for(int i=0; i<n; i++){
        double temp; fin>>temp;
        a.push_back(temp);
        if(temp!=(int)(temp)){
            suntIntregi=false;
        }
        aInt.push_back((int)(temp));
    }
    auto lo=chrono::high_resolution_clock::now();
    heapsort(a, n);
    auto hi=chrono::high_resolution_clock::now();
    chrono::duration<double>ans=hi-lo;
    fout<<ans.count()<<"\n";
    return 0;
}
