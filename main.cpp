#include <fstream>
#include <iostream>
#include<cstring>
#include<queue>
using namespace std;
ifstream fin("siruri.txt");
ofstream fout("timpi.txt");
///pentru simplitate, sa presupunem ca nu sunt chei negative
bool isSorted(int a[], int n){
    for(int i=1; i<n; i++)
        if(a[i]<a[i-1])
          return false;
    return true;
}
void bubble(double a[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++)
            if(a[j]>a[j+1])
              swap(a[j], a[j+1]);
    }
}
const int MAXR=1e8;
int ct[MAXR];
void counting(int a[], int n){
    int lo=1e9, hi=-1;
    for(int i=0; i<n; i++){
        lo=min(lo, a[i]);
        hi=max(hi, a[i]);
    }///la counting, vectorul e automat normalizat
    if(hi-lo>1e8){
        fout<<"NU SE POATE FACE COUNTING SORT\n";
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
void shellSort(int a[], int n){
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
///mergesort
void merging(int a[], int lo, int mid, int hi){
    const int MAXR=1e4;
    int L[MAXR];///aici vom pune interclasarea
    int i=lo, j=mid+1, k=0;
    while((i<mid+1)&&(j<hi+1)){
        if(a[i]<a[j]){
            L[k]=a[i], k++, i++;
        }
        else{
            L[k]=a[j], k++, j++;
        }
        if(i==mid+1)
            while(j<hi+1)
              L[k]=a[j], k++, j++;
        if(j==hi+1)
            while(i<mid+1)
              L[k]=a[i], k++, i++;
    }
    for(int i=lo; i<=hi; i++)
        a[i]=L[i-lo];
}
void mergesort(int a[], int lo, int hi){///va fi nevoie de apeluri recursive
   if(lo<hi){
      int mid=lo+(hi-lo)/2;
      mergesort(a, lo, mid);
      mergesort(a, mid+1, hi);
      merging(a, lo, mid, hi);
   }
}
///quicksort va avea functia de pivotare separata
int pivotare(int a[], int lo, int hi){
     int pivot=a[lo], index=hi; ///pivotul e prima chestie, nu da in patrat
     for(int i=hi; i>lo; i--){
         if(a[i]>pivot){
            swap(a[i], a[index]);
            index--;
         }
     }
     swap(a[index], a[lo]);
     return index;
}
void quicksort(int a[], int lo, int hi){
   if(lo<hi){
      int pivot=pivotare(a, lo, hi);///pivotarea intoarce locul unde se va afla pivotul
      quicksort(a, lo, pivot-1);
      quicksort(a, pivot+1, hi);
   }
}
void heapsort(int a[], int n){
    priority_queue<int> pq;
    for(int i=0; i<n; i++)
        pq.push(a[i]);
    for(int i=0; i<n; i++){
        a[n-i-1]=pq.top();
        pq.pop();
    }
}
void radixSort(int a[], int n, int base)
{
    queue<int> buc[BMAX];///bucket-urile in care punem numerele in functie de cifra de pe pozitia j
    int maxx=0,ct=0;
    for(int i=0;i<n;i++)
    {
        if(maxx<a[i])
        {
            maxx=a[i];
        }
    }
    while(maxx>0)
    {
        maxx/=base;
        ct++;
    }
    int po=1;
    int cif;
    int it=0;
    for(int j=0;j<ct;j++)
    {
        for(int i=0;i<n;i++)
        {
            cif=(a[i]/po)%base;
            buc[cif].push(a[i]);
        }
        it=0;
        for(int i=0;i<base;i++)
        {
            while(!buc[i].empty())
            {
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
    int a[7]={2, 4, 5, 7, 1, 6, 3};
    radixSort(a, 7, 4);
    for(int i=0; i<7; i++)
        cout<<a[i]<<" ";
    return 0;
}
