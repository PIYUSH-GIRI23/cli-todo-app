#include <bits/stdc++.h>
using namespace std;

const string FILE_PATH = string(getenv("HOME")) + "/.mytodo_store.txt";

int editDistance(const string &a, const string &b){
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = (a[i - 1] == b[j - 1])
                           ? dp[i - 1][j - 1]
                           : 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[n][m];
}

string currentDateTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

struct Todo{
    int id;
    string name, desc, datetime;
};

vector<Todo> loadTodos(){
    vector<Todo> todos;
    try{
        ifstream fin(FILE_PATH);
        if (!fin.is_open())
            return todos;
        string line;
        while (getline(fin, line)){
            if (line.empty())
                continue;
            stringstream ss(line);
            Todo t;
            string tmp;
            getline(ss, tmp, '|');
            t.id = stoi(tmp);
            getline(ss, t.name, '|');
            getline(ss, t.desc, '|');
            getline(ss, t.datetime, '|');
            todos.push_back(t);
        }
    }
    catch (exception &e){
        cerr << "Error reading file: " << e.what() << "\n";
    }
    return todos;
}

void saveTodos(const vector<Todo> &todos){
    try{
        ofstream fout(FILE_PATH);
        if (!fout.is_open())
            throw runtime_error("Cannot open database file for writing.");
        for (auto &t : todos)
            fout << t.id << "|" << t.name << "|" << t.desc << "|" << t.datetime << "|\n";
    }
    catch (exception &e){
        cerr << "Error writing file: " << e.what() << "\n";
    }
}

bool nameExists(const vector<Todo> &todos, const string &name){
    for (auto &t : todos)
        if (t.name == name)
            return true;
    return false;
}

int nextId(const vector<Todo> &todos){
    int mx = 0;
    for (auto &t : todos)
        mx = max(mx, t.id);
    return mx + 1;
}


void showHelp(const vector<string> &cmds, const vector<string> &desc){
    cout << "Available commands:\n\n";
    for (int i = 0; i < cmds.size(); i++)
        cout << "  " << setw(35) << left << cmds[i] << " → " << desc[i] << "\n";
}

// ------------------- Suggest Base Command -------------------
void suggestCommand(const string &program, const string &given, const vector<string> &valid)
{
    vector<pair<int, string>> dist;
    for (auto &cmd : valid)
        dist.push_back({editDistance(given, cmd), cmd});
    sort(dist.begin(), dist.end());

    bool found = false;
    for (auto &p : dist)
        if (p.first <= 3) found = true;

    if (found){
        cout << "\nDid you mean:\n";
        for (auto &p : dist)
        {
            if (p.first <= 3)
                cout << "  " << p.second << "\n";
        }
    }
    else{
        // Simple message when no close match
        cout << "'" << given << "' is not a mytodo command. See 'mytodo help' for available commands.\n";
    }
}



// ------------------- MAIN -------------------
int main(int argc, char *argv[]){
    string program = "mytodo";
    vector<string> baseCmds = {"add", "list", "delete", "uninstall", "help"};
    vector<string> fullCmds = {
        "mytodo add -n <name> -d <description>",
        "mytodo list",
        "mytodo list all",
        "mytodo delete -i <id>",
        "mytodo delete all",
        "mytodo uninstall",
        "mytodo help"};
    vector<string> desc = {
        "Add a new todo (usage: mytodo add -n <name> -d <desc>)",
        "List all todos (usage: mytodo list)",
        "List all todos in detail (usage: mytodo list all)",
        "Delete a todo by ID (usage: mytodo delete -i <id>)",
        "Delete all todos (usage: mytodo delete all)",
        "Uninstall the application",
        "Show this help menu"};

    if (argc < 2){
        cout << "Usage: mytodo <command>\n";
        cout << "Try 'mytodo help' to see available commands.\n";
        return 0;
    }

    string cmd = argv[1];

    if (cmd == "help" || cmd == "-h" || cmd == "--help"){
        showHelp(fullCmds, desc);
    }

    else if (cmd == "add" || cmd == "-a"){
        if (argc == 6 && string(argv[2]) == "-n" && string(argv[4]) == "-d"){
            string name = argv[3], desc = argv[5];
            auto todos = loadTodos();
            if (nameExists(todos, name)){
                cout << "⚠️  Task with name '" << name << "' already exists.\n";
                return 0;
            }
            Todo t{nextId(todos), name, desc, currentDateTime()};
            todos.push_back(t);
            saveTodos(todos);
            cout << "[✔] Added task '" << name << "' (ID: " << t.id << ")\n";
        }
        else{
            cout << "Command not valid: ";
            for (int i = 1; i < argc; i++)
                cout << argv[i] << " ";
            cout << "\nUsage: mytodo add -n <name> -d <description>\n";
        }
    }

    else if (cmd == "list" || cmd == "-l"){
        auto todos = loadTodos();
        if (todos.empty()){
            cout << "No tasks found.\n";
            return 0;
        }

        int w_id = 10, w_name = 25, w_desc = 40, w_datetime = 20;

        if (argc == 2){
            // Normal list (ID, Name, Description)
            cout << left << setw(w_id) << "ID"
                 << setw(w_name) << "Name"
                 << setw(w_desc) << "Description" << "\n";
            cout << string(w_id + w_name + w_desc, '-') << "\n";

            for (auto &t : todos)
                cout << left << setw(w_id) << t.id
                     << setw(w_name) << t.name
                     << setw(w_desc) << t.desc << "\n";
        }
        else if (argc == 3){
            // detailed list
            string flag = argv[2];
            if (flag == "all" || flag == "-a"){
                cout << left << setw(w_id) << "ID"
                     << setw(w_name) << "Name"
                     << setw(w_desc) << "Description"
                     << setw(w_datetime) << "Date & Time" << "\n";
                cout << string(w_id + w_name + w_desc + w_datetime, '-') << "\n";

                for (auto &t : todos)
                    cout << left << setw(w_id) << t.id
                         << setw(w_name) << t.name
                         << setw(w_desc) << t.desc
                         << setw(w_datetime) << t.datetime << "\n";
            }
            else{
                cout << program << ": unknown option '" << flag << "' for 'list'\n";
                cout << "Try '" << program << " help' to see available commands.\n";
            }
        }
        else
        {
            cout << program << ": too many arguments for 'list'\n";
            cout << "Try '" << program << " help' to see available commands.\n";
        }
    }
    
    else if (cmd == "delete" || cmd == "-d"){
        auto todos = loadTodos();
        if (argc == 4 && string(argv[2]) == "-i"){
            try{
                int id = stoi(argv[3]);
                auto it = find_if(todos.begin(), todos.end(), [&](const Todo &t)
                                  { return t.id == id; });
                if (it == todos.end()){
                    cout << "❌ No task found with ID " << id << "\n";
                }
                else{
                    cout << "[✔] Deleted task '" << it->name << "' (ID: " << id << ")\n";
                    todos.erase(it);
                    saveTodos(todos);
                }
            }
            catch (...)
            {
                cout << "❌ Invalid ID provided.\n";
            }
        }
        else if (argc == 3 && string(argv[2]) == "all"){
            todos.clear();
            saveTodos(todos);
            cout << "[✔] All tasks deleted.\n";
        }
        else{
            cout << program << ": invalid arguments for 'delete'\n";
            cout << "Try '" << program << " help' to see available commands.\n";
        }
    }

    else if (cmd == "uninstall" || cmd == "-u"){
        cout << "[⚙] Running uninstall script..." << endl;
        int ret = system("bash /usr/local/bin/uninstall_mytodo.sh");
        if (ret != 0){
            cerr << "❌ Failed to run uninstall script. Make sure it exists and is executable." << endl;
        }
    }

    else{
        suggestCommand(program, cmd, baseCmds);
    }

    return 0;
}
