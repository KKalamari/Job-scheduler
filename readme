## Project Description
This project implements a job management system using pipes and signals for inter-process communication. The system includes a server (`jobexecutorserver`)
that executes jobs and a client (`jobcommander`) that communicates with the server to submit, manage, and monitor jobs.

---

## Table of Contents
- [How to Run the Program](#how-to-run-the-program)
- [Communication Structure](#communication-structure)
- [File Descriptions](#file-descriptions)
- [Available Commands](#available-commands)
- [Bash Scripts](#bash-scripts)
- [Implementation Notes](#implementation-notes)

---

## How to Run the Program

2. **Compile the project**
   ```bash
   make
   ```

3. **Execute commands using `jobcommander`**
   ```bash
   ./jobcommander [options]
   ```

4. **Clean up files after exiting**
   ```bash
   make clean
   ```

---

## Communication Structure

- `pipe1`: The `jobcommander` writes here, and the `jobexecutorserver` reads from it.
- `pipe2`: The `jobexecutorserver` writes here, and the `jobcommander` reads from it.

---

## File Descriptions

### Executable Programs

- **`jobcommander`**: 
  - Checks if the file `jobexecutorserver.txt` exists. If not, it starts the server.
  - Reads the server’s PID from the file and opens the FIFOs.
  - Converts terminal arguments into a single space-separated string.
  - Sends a `SIGUSR1` signal to the server, instructing it to read from `pipe1` and execute the command.

- **`jobexecutorserver`**:
  - Runs in an infinite loop (`while`) waiting for signals.
  - Reads commands from `pipe1` and executes the corresponding function via a `switch-case` statement.
  - Handles `SIGUSR1` and `SIGCHLD` signals.
  - `SIGUSR1` notifies the server to read a new command from `pipe1`.
  - `SIGCHLD` registers completed processes and removes them from the running jobs list.

---

## Available Commands

- **`issuejob`**: Creates and adds a new job to the queue.
- **`stop`**: Stops a job that is either running or queued.
- **`poll running`**: Returns currently active jobs.
- **`poll queued`**: Returns jobs waiting in the execution queue.

---

## Bash Scripts

- **`multijob.sh`**:
  - Reads and executes commands from files line by line.

- **`allJobsStop.sh`**:
  - Retrieves active and queued jobs.
  - Stops all running jobs using `jobcommander stop`.

---

## Implementation Notes

- The `jobexecutorserver` uses a queue (`the_one queue`) to store pending jobs and a vector (`running vector`) to track currently executing jobs.
- Jobs are executed using `fork` and `execvp`.
- Information is returned to `jobcommander` via `pipe2`.



