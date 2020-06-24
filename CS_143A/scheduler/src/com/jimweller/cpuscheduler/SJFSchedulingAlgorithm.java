/** SJFSchedulingAlgorithm.java
 * 
 * A shortest job first scheduling algorithm.
 *
 * @author: Charles Zhu
 * Spring 2016
 *
 */
package com.jimweller.cpuscheduler;

import java.util.*;

import com.jimweller.cpuscheduler.Process;

public class SJFSchedulingAlgorithm extends BaseSchedulingAlgorithm implements OptionallyPreemptiveSchedulingAlgorithm {
    
    private ArrayList<Process> jobs;
    private boolean preemptive;

    SJFSchedulingAlgorithm(){
	activeJob = null;
	jobs = new ArrayList<Process>();
    }

    /** Add the new job to the correct queue.*/
    public void addJob(Process p){
	jobs.add(p);
    }
    
    /** Returns true if the job was present and was removed. */
    public boolean removeJob(Process p){
	if (p == activeJob)
	    activeJob = null;

	return jobs.remove(p);
    }

    /** Transfer all the jobs in the queue of a SchedulingAlgorithm to another, such as
    when switching to another algorithm in the GUI */
    public void transferJobsTo(SchedulingAlgorithm otherAlg) {
        throw new UnsupportedOperationException();
    }

    /** Returns the next process that should be run by the CPU, null if none available.*/
    public Process getNextJob(long currentTime){
	Process shortest = null;
	
	if (!isPreemptive())
	    if (!isJobFinished())
		return activeJob;
	for (int i = 0; i < jobs.size(); i++) {
	    Process thisJob = jobs.get(i);
	    if (i == 0)
		shortest = thisJob;
	    else if (thisJob.getBurstTime() == shortest.getBurstTime() &&
		     thisJob.getPID() < shortest.getPID())
		shortest = thisJob;
	    else if (thisJob.getBurstTime() < shortest.getBurstTime())
		shortest = thisJob;
	}

	activeJob = shortest;
	return activeJob;
    }

    public String getName(){
        return "Shortest Job First";
    }

    /**
     * @return Value of preemptive.
     */
    public boolean isPreemptive(){
	return preemptive;
    }
    
    /**
     * @param v  Value to assign to preemptive.
     */
    public void setPreemptive(boolean  v){
	preemptive = v;
    }
    
}
