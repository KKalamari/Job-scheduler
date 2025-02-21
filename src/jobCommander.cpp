#include "commander.h"
#include <sstream>

int main(int argc, char *argv[]) 
{
    ifstream file("jobExecutorServer.txt");
    if (!file) // if the file doesn't exist , execute the server 
    {
        pid_t childpid = fork();
        if (childpid < 0) 
        {
            cerr << "Fork failed." << endl;
        } else if (childpid == 0) 
        {
            execl("jobExecutorServer", "./jobExecutorServer", NULL);
        }else 
        {
            sleep(2); //need some time to create the txt filer       
            file.close();
            file.open("jobExecutorServer.txt");//reopen the file so that file>>pid succeeds
        }

    }
    int pid; //take the server pid from the file 
    if(!(file>>pid)){
        cout<<"read wrong"<<endl;
    }

    file.close();
    int pipe1_fd;
    int pipe2_fd;

    mkfifo("pipe1", 0666);
    mkfifo("pipe2", 0666);

    pipe1_fd = open("pipe1", O_RDWR); //open the pieps for talking
    pipe2_fd =open("pipe2", O_RDWR);

    if (pipe1_fd == -1 || pipe2_fd == -1) //check if the pipes were opened correctly
    {
        cerr << "error opening pipes." << endl;
        return 1;
    }

      
    if (argc < 2) // check if a job was given
    {
        cerr << "please give a job" << endl;
        return 1;
    }

    //give a space char between the arguments and turn it into a string
    string command = argv[1]; // without this i would also get the first space into the command and i don't want that
    for (int i = 2; i < argc; ++i) 
    {
        command += " ";
        command += argv[i];

    }

    kill (pid, SIGUSR1);//signal for the server to read

    if (write(pipe1_fd, command.c_str(), command.size())== -1)// write the string command into the pipe (use command.c_str so that the write works)
    {
        cout<<"error in writing in the pipe"<<endl;
        return 0;
    }

    char buffer[256];
    //wait for a response to print, if its "end" then just end the programm
    //this message is only send when setconcurrency is used, or invalid command
    ssize_t bytes_read = read(pipe2_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) 
    {
        cerr << "error reading from pipe." << endl;
    }
    buffer[bytes_read] = '\0';//i need it to bee null terminated string for the strcpm to work

    if(strcmp(buffer,"end")==0) 
    {
        close(pipe1_fd);
        close(pipe2_fd);

        return 0;
    }
    cout << buffer <<"\n"<< endl; //pritns the server's message

    //closes the pipes
    close(pipe1_fd);
    close(pipe2_fd);
 

    return 0;
}
