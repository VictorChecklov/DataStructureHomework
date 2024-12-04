#include <iostream>
#include <cstring>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

constexpr size_t MAX_LENGTH = 15;
constexpr size_t MAX_VOLUNTEERS = 150;

struct Volunteer {
    char number[MAX_LENGTH]{};
    char name[MAX_LENGTH]{};
    char phone[MAX_LENGTH]{};
    float hours{};

    Volunteer() = default;
    Volunteer(const char* num, const char* nam, const char* pho) {
        strncpy(number, num, MAX_LENGTH - 1);
        strncpy(name, nam, MAX_LENGTH - 1);
        strncpy(phone, pho, MAX_LENGTH - 1);
        hours = 0.0f;
    }
};

class VolunteerManagement {
public:
    VolunteerManagement() : length(0) {}

    void add(const Volunteer& vol);
    void insert(const Volunteer& vol, int pos);
    int find(const char* data, int field) const;
    void edit(const char* target, float target2, int index, int choice);
    void remove(const char* num);
    void q_sort(int left, int right);
    void show() const;
    void show_single(int pos) const;
    void refresh() const;
    void init();

    [[nodiscard]] int get_length() const { return length; }

private:
    Volunteer volunteer[MAX_VOLUNTEERS];
    int length;
};

void VolunteerManagement::add(const Volunteer& vol) {
    if (length >= MAX_VOLUNTEERS) throw invalid_argument("Add: List is Full!");
    volunteer[length++] = vol;
}

void VolunteerManagement::insert(const Volunteer& vol, int pos) {
    if (length >= MAX_VOLUNTEERS || pos < 1 || pos > length + 1)
        throw invalid_argument("Insert: Invalid position or List is Full!");

    for (int i = length; i > pos - 1; --i) {
        volunteer[i] = volunteer[i - 1];
    }
    volunteer[pos - 1] = vol;
    length++;
}

int VolunteerManagement::find(const char* data, int field) const {
    if (length == 0) throw invalid_argument("Find: List is Empty!");

    for (int i = 0; i < length; ++i) {
        if ((field == 1 && strcmp(data, volunteer[i].number) == 0) ||
            (field == 2 && strcmp(data, volunteer[i].name) == 0)) {
            return i;
        }
    }
    throw invalid_argument("Find: Not Found!");
}

void VolunteerManagement::edit(const char* target, float target2, int index, int choice) {
    switch (choice) {
    case 1: strncpy(volunteer[index].number, target, MAX_LENGTH - 1); break;
    case 2: strncpy(volunteer[index].name, target, MAX_LENGTH - 1); break;
    case 3: strncpy(volunteer[index].phone, target, MAX_LENGTH - 1); break;
    case 4: volunteer[index].hours = target2; break;
    default: throw invalid_argument("Edit: Invalid User Choice!");
    }
}

void VolunteerManagement::remove(const char* num) {
    if (length == 0) throw invalid_argument("Remove: List is Empty!");

    for (int i = 0; i < length; ++i) {
        if (strcmp(num, volunteer[i].number) == 0) {
            for (int j = i; j < length - 1; ++j) {
                volunteer[j] = volunteer[j + 1];
            }
            --length;
            return;
        }
    }
    throw invalid_argument("Remove: Not Found!");
}

void VolunteerManagement::q_sort(int left, int right) {// NOLINT(*-no-recursion)
    if (left >= right) return;
    float pivot = volunteer[right].hours;
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (volunteer[j].hours <= pivot) {
            swap(volunteer[++i], volunteer[j]);
        }
    }
    swap(volunteer[++i], volunteer[right]);
    q_sort(left, i - 1);
    q_sort(i + 1, right);
}

void VolunteerManagement::show() const {
    cout << "========== Volunteer Management System ==========\n"
        << "|| 1 - Add                2 - Insert           ||\n"
        << "|| 3 - Edit               4 - Delete           ||\n"
        << "|| 5 - Sort               0 - Exit             ||\n"
        << "=================================================\n";
    cout << "Total: " << length << endl;
    for (int i = 0; i < length; ++i) {
        cout << left
            << setw(15) << volunteer[i].number
            << setw(15) << volunteer[i].name
            << setw(15) << volunteer[i].phone
            << setw(10) << volunteer[i].hours << endl;
    }
    cout << "-------------------------------------------------" << endl;
}


void VolunteerManagement::show_single(int pos) const {
    cout << left
        << setw(15) << volunteer[pos].number
        << setw(15) << volunteer[pos].name
        << setw(15) << volunteer[pos].phone
        << setw(10) << volunteer[pos].hours << endl;
}

void VolunteerManagement::refresh() const {
    cout << "\033[2J\033[H"; // 清屏
    show();
}

void VolunteerManagement::init() {
    add(Volunteer("2024001", "a", "123456"));
    add(Volunteer("2024002", "b", "123457"));
    add(Volunteer("2024003", "c", "123458"));
    add(Volunteer("2024004", "d", "123459"));
    add(Volunteer("2024005", "e", "123460"));
    add(Volunteer("2024006", "f", "123461"));
    add(Volunteer("2024007", "g", "123462"));
    add(Volunteer("2024008", "h", "123463"));
    add(Volunteer("2024009", "i", "123464"));
    add(Volunteer("2024010", "j", "123465"));
}

int main() {
    VolunteerManagement v;
    v.init();

    while (true) {
        v.refresh();
        int menu_choice;
        cout << "Enter your choice: ";
        cin >> menu_choice;

        // 错误处理：如果输入无效，清除输入并提示重新输入
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }

        try {
            switch (menu_choice) {
            case 1: {
                int n;
                cout << "Number of volunteers: ";
                cin >> n;
                while (n--) {
                    v.refresh();
                    cout << "Add: Remain:" << n << endl;
                    char num[MAX_LENGTH], nam[MAX_LENGTH], pho[MAX_LENGTH];
                    cout << "Number: "; cin >> num;
                    cout << "Name: "; cin >> nam;
                    cout << "Phone: "; cin >> pho;
                    v.add(Volunteer(num, nam, pho));
                }
                break;
            }
            case 2: {
                int pos;
                char num[MAX_LENGTH], nam[MAX_LENGTH], pho[MAX_LENGTH];
                cout << "Insert position: "; cin >> pos;
                cout << "Number: "; cin >> num;
                cout << "Name: "; cin >> nam;
                cout << "Phone: "; cin >> pho;
                v.insert(Volunteer(num, nam, pho), pos);
                break;
            }
            case 3: {
                int select_choice;
                char target_data[MAX_LENGTH];
                cout << "Select by (1 - Number, 2 - Name): ";
                cin >> select_choice;
                cout << "Target data: "; cin >> target_data;

                int pos = v.find(target_data, select_choice);
                v.refresh();
                cout << "Editing...\n";
                v.show_single(pos);

                int change_choice;
                cout << "Which data to edit (1 - Number, 2 - Name, 3 - Phone, 4 - Hours): ";
                cin >> change_choice;

                switch (change_choice) {
                case 1: {
                    char number[MAX_LENGTH];
                    cout << "Enter new number: "; cin >> number;
                    v.edit(number, 0.0, pos, change_choice);
                    break;
                }
                case 2: {
                    char name[MAX_LENGTH];
                    cout << "Enter new name: "; cin >> name;
                    v.edit(name, 0.0, pos, change_choice);
                    break;
                }
                case 3: {
                    char phone[MAX_LENGTH];
                    cout << "Enter new phone: "; cin >> phone;
                    v.edit(phone, 0.0, pos, change_choice);
                    break;
                }
                case 4: {
                    float hours;
                    cout << "Enter new hours: "; cin >> hours;
                    v.edit("", hours, pos, change_choice);
                    break;
                }
                default: {
                    cout << "Invalid input. Please enter a valid choice.\n";
                    break;
                }
                }
                break;
            }
            case 4: {
                char number[MAX_LENGTH];
                cout << "Enter volunteer number to delete: ";
                cin >> number;
                v.remove(number);
                break;
            }
            case 5: {
                cout << "Sorting volunteers...\n";
                v.q_sort(0, v.get_length() - 1);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please select again.\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
