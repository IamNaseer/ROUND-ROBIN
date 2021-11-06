#include<iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,starttime;
  int btremaining;
}ps[10];

bool comparingAT(struct process_struct a,struct process_struct b)
{
   int x =a.at;
   int y =b.at;
   return x < y;

}

bool comparingPID(struct process_struct a,struct process_struct b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}

int main()
{

    int n,index;
    int cpuutilization;
    queue<int> q;
    bool visited[50]={false},isfirstprocess=true;
    int currenttime = 0,maxcompletiontime;
    int completed = 0,tq, totalidletime=0;
    cout<<"Enter total number of processes: ";
    cin>>n;
    float sumoftat=0,sumofwt=0,sumofrt=0;

    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< " Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid=i;
    }

    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< " Burst Time: ";
        cin >> ps[i].bt;
        ps[i].btremaining= ps[i].bt;
    }

    cout<<"\nEnter time quanta: ";
    cin>>tq;
    sort(ps,ps+n,comparingAT);

    q.push(0);
    visited[0] = true;

    while(completed != n)
    {
      index = q.front();
      q.pop();

      if(ps[index].btremaining == ps[index].bt)
      {
            ps[index].starttime = max(currenttime,ps[index].at);
            totalidletime += (isfirstprocess == true) ? 0 : ps[index].starttime - currenttime;
            currenttime =  ps[index].starttime;
            isfirstprocess = false;

      }

      if(ps[index].btremaining-tq > 0)
      {
            ps[index].btremaining -= tq;
            currenttime += tq;
      }
      else
      {
            currenttime += ps[index].btremaining;
            ps[index].btremaining = 0;
            completed++;

            ps[index].ct = currenttime;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].starttime - ps[index].at;

            sumoftat += ps[index].tat;
            sumofwt += ps[index].wt;
            sumofrt += ps[index].rt;
      }
      for(int i = 1; i < n; i++)
      {
          if(ps[i].btremaining > 0 && ps[i].at <= currenttime && visited[i] == false)
          {
            q.push(i);
            visited[i] = true;
          }
      }
      if( ps[index].btremaining> 0)
          q.push(index);
      if(q.empty())
      {
          for(int i = 1; i < n; i++)
          {
            if(ps[i].btremaining > 0)
            {
              q.push(i);
              visited[i] = true;
              break;
            }
          }
      }
   }
  maxcompletiontime = INT_MIN;
  for(int i=0;i<n;i++)
        maxcompletiontime = max(maxcompletiontime,ps[i].ct);
  sort(ps, ps+n , comparingPID);

  cout<<"\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i=0;i<n;i++)
     cout<<i<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
    cout<<endl;
    cout<<"\nAverage Turn Around time= "<< sumoftat/n;
    cout<<"\nAverage Waiting Time= "<<sumofwt/n;
    cout<<"\nAverage Response Time= "<<sumofrt/n;
}
