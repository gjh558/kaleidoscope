#include <string>
#include <iostream>
#include <vector>

using namespace std;

template<class C, class S> size_t split_q(const S &s, C& c, char delim, char quote = '"')
        {
         	size_t length = s.length();

                size_t start  = 0, n = 0;
                while(start < length)
                {
                 	size_t i = start;

                        bool skipping = false;
			while (i < length)
                        {
                                if (s[i] == quote)
				{
                                        ++i;
                                        skipping = true;
                                        while (i < length && s[i] != quote) ++i;
                                }

                                if (skipping)
                                {
                                        if (i == length)
                                                break;

                                        ++i;
                                        skipping = false;
                                        continue;
				}

                                if (s[i] == delim)
					break;

                                ++i;
			}

                        if (i >= length)
                        {
                         	c.push_back(s.substr(start));
                                start = length;
				++n;
                        }
                        else
	 	        {
                         	c.push_back(s.substr(start, i -  start));
                                ++n;
                                start = i + 1;
                        }
		}

                return n;
	}

int main() {
	vector<string> strs;
        string s = "hello world, I said.";
        split_q(s, strs, ' ', ',');

        for (const string& s : strs) {
		cout << s << endl;
        }
        return 0;
}
