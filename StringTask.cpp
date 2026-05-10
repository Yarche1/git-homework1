#include <iostream>
using namespace std;

class String {
    char* ptr;
    int length;

    int GetStrLen(const char* s) const {
        int len = 0;
        while (s[len] != '\0') len++;
        return len;
    }

public:
    const char* GetData() const { return ptr; }
    int GetLength() const { return length; }

    String() {
        length = 0;
        ptr = new char[1];
        ptr[0] = '\0';
    }

    String(const char* s) {
        length = 0;
        ptr = new char[1];
        ptr[0] = '\0';
        Append(s);
    }

    ~String() { delete[] ptr; }

    void Print() const { cout << ptr << endl; }

    void Append(const char* s, int s_len = -1) {
        if (s_len < 0) s_len = GetStrLen(s);
        int new_len = length + s_len;
        char* new_ptr = new char[new_len + 1];
        for (int i = 0; i < length; i++) new_ptr[i] = ptr[i];
        for (int i = 0; i < s_len; i++) new_ptr[length + i] = s[i];
        new_ptr[new_len] = '\0';
        delete[] ptr;
        ptr = new_ptr;
        length = new_len;
    }


    bool Contains(const char* sub) const {
        int sub_len = GetStrLen(sub);
        if (sub_len == 0) return true;
        for (int i = 0; i <= length - sub_len; i++) {
            bool match = true;
            for (int j = 0; j < sub_len; j++) {
                if (ptr[i + j] != sub[j]) { match = false; break; }
            }
            if (match) return true;
        }
        return false;
    }


    int Count(const char* sub) const {
        int sub_len = GetStrLen(sub);
        if (sub_len == 0) return 0;
        int count = 0;
        for (int i = 0; i <= length - sub_len; i++) {
            bool match = true;
            for (int j = 0; j < sub_len; j++) {
                if (ptr[i + j] != sub[j]) { match = false; break; }
            }
            if (match) { count++; i += sub_len - 1; }
        }
        return count;
    }

    
    void Insert(int pos, const char* sub) {
        if (pos < 0 || pos > length) return;
        int sub_len = GetStrLen(sub);
        int new_len = length + sub_len;
        char* new_ptr = new char[new_len + 1];
        for (int i = 0; i < pos; i++) new_ptr[i] = ptr[i];
        for (int i = 0; i < sub_len; i++) new_ptr[pos + i] = sub[i];
        for (int i = pos; i < length; i++) new_ptr[i + sub_len] = ptr[i];
        new_ptr[new_len] = '\0';
        delete[] ptr;
        ptr = new_ptr;
        length = new_len;
    }

    
    void Remove(const char* old_sub, const char* new_sub) {
        int old_len = GetStrLen(old_sub);
        int new_sub_len = GetStrLen(new_sub);
        if (old_len == 0) return;

        int count = Count(old_sub);
        if (count == 0) return;

        int new_total_length = length - (count * old_len) + (count * new_sub_len);
        char* new_ptr = new char[new_total_length + 1];
        int write_idx = 0;

        for (int i = 0; i < length; ) {
            bool match = true;
            if (i <= length - old_len) {
                for (int j = 0; j < old_len; j++) {
                    if (ptr[i + j] != old_sub[j]) { match = false; break; }
                }
            } else match = false;

            if (match) {
                for (int j = 0; j < new_sub_len; j++) new_ptr[write_idx++] = new_sub[j];
                i += old_len;
            } else {
                new_ptr[write_idx++] = ptr[i++];
            }
        }
        new_ptr[new_total_length] = '\0';
        delete[] ptr;
        ptr = new_ptr;
        length = new_total_length;
    }
};

int main() {
    String s("Hello world");
    cout << "Original: "; s.Print();

    cout << "Contains 'world': " << (s.Contains("world") ? "Yes" : "No") << endl;

    s.Insert(6, "beautiful ");
    cout << "After Insert: "; s.Print();

    String s2("one two one two");
    cout << "Before Replace: "; s2.Print();
    s2.Remove("one", "three");
    cout << "After Replace: "; s2.Print();

    cout << "Count of 'two' in string: " << s2.Count("two") << endl;

    return 0;
}
