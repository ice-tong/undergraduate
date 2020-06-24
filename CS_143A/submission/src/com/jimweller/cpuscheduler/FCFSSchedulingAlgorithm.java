/** FCFSSchedulingAlgorithm.java
 * 
 * A first-come first-served scheduling algorithm.
 * The current implementation will work without memory management features
 *
 */
package com.jimweller.cpuscheduler;

import java.util.*;

class Block {
    private long hole;
    private boolean occupied;
    private long PID;

    Block(long value) {
	this.hole = value;
	this.occupied = false;
    }

    public long getHole() {
	return this.hole;
    }

    public void setHole(long v) {
	this.hole = v;
    }

    public boolean isOccupied() {
	return this.occupied;
    }

    public void occupy(long ID) {
	this.occupied = true;
	this.PID = ID;
    }

    public void free() {
	this.occupied = false;
	this.PID = 0;
    }

    public long getID() {
	return this.PID;
    }
}

public class FCFSSchedulingAlgorithm extends BaseSchedulingAlgorithm {

	private ArrayList<Process> jobs;

	private String memStyle;
	private ArrayList<Block> blocks;

	class FCFSComparator implements Comparator<Process> {
		public int compare(Process p1, Process p2) {
			if (p1.getArrivalTime() != p2.getArrivalTime()) {
				return Long.signum(p1.getArrivalTime() - p2.getArrivalTime());
			}
			return Long.signum(p1.getPID() - p2.getPID());
		}
	}

	FCFSComparator comparator = new FCFSComparator();

	FCFSSchedulingAlgorithm() {
		activeJob = null;
		jobs = new ArrayList<Process>();

		blocks = new ArrayList<Block>();
		blocks.add(new Block(380));
	}


	/** Add the new job to the correct queue. */
	public void addJob(Process p) {

	if (this.memStyle == "first" || this.memStyle == "best") {
	
	boolean fitted = false;
	long memSize = p.getMemSize();
	long PID = p.getPID();

	for (int i = 0; i < blocks.size(); i++) {
	    Block block = blocks.get(i);
	    long hole = block.getHole();

	    if (!block.isOccupied()) {
	        if (hole > memSize) {
		    block.setHole(hole - memSize);
		    Block new_block = new Block(memSize);
		    new_block.occupy(PID);
		    blocks.add(0, new_block);
		    fitted = true;
		    break;
	        }
	        if (hole == memSize) {
		    block.occupy(PID);
		    fitted = true;
		    break;
	        }
	    }
	}

	if (!fitted) {
 	    p.setIgnore(true);
 	    return;
	}
	}

		jobs.add(p);
		Collections.sort(jobs, comparator);
	}

	/** Returns true if the job was present and was removed. */
	public boolean removeJob(Process p) {
		if (p == activeJob)
			activeJob = null;

		if (this.memStyle == "first" || this.memStyle == "best") {

		long memSize = p.getMemSize();
		long PID = p.getPID();

		if (blocks.size() == 1) {
		    blocks.get(0).free();
		    return jobs.remove(p);
		}

		for (int i = 0; i < blocks.size(); i++) {
		    Block block = blocks.get(i);
		    long hole = block.getHole();

		    if (block.isOccupied() && block.getID() == PID) {
			if (i >= 0 && i < blocks.size()-1) {
			    Block next_block = blocks.get(i+1);
			    if (!next_block.isOccupied()) {
				block.setHole(hole + next_block.getHole());
				blocks.remove(next_block);
				block.free();
				break;
			    }
			}
			if (i >= 1 && i <= blocks.size()-1) {
			    Block prev_block = blocks.get(i-1);
			    if (!prev_block.isOccupied()) {
				block.setHole(hole + prev_block.getHole());
				blocks.remove(prev_block);
				block.free();
				break;
			    }
			}
		    }
		}
		}

		return jobs.remove(p);
	}

	/**
	 * Transfer all the jobs in the queue of a SchedulingAlgorithm to another, such
	 * as when switching to another algorithm in the GUI
	 */
	public void transferJobsTo(SchedulingAlgorithm otherAlg) {
		throw new UnsupportedOperationException();
	}

	/**
	 * Returns the next process that should be run by the CPU, null if none
	 * available.
	 */
	public Process getNextJob(long currentTime) {
		Process earliest = null;

		if (!isJobFinished())
			return activeJob;
		if (jobs.size() > 0)
			earliest = jobs.get(0);
		activeJob = earliest;
		return activeJob;
	}

	public String getName() {
		return "First-Come First-Served";
	}

	public void setMemoryManagment(String v) {
		memStyle = v.toLowerCase();
	}
}
