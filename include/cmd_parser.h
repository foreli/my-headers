#ifndef TRIES_CMD_PARSER_H
#define TRIES_CMD_PARSER_H


#include "mstring.h"
#include "hash_table.h"

#define UNKNOWN_ARG 1
#define WRONG_FORMAT 2
#define WRONG_INPUT 3
#define SUCCESS 4


/*
 * Simple command line arguments parser. Expects an mstd::hash_table object
 * with entries in the form of: "argument-name" => "<s/i/none>"
 * and parses the command line arguments trying to match them
 */

namespace mstd {
    class cmd_parser {
    private:
        mstd::hash_table<mstd::string> _s_args;
        mstd::hash_table<int> _i_args;
        mstd::vector<mstd::string> _unaries;
    public:
        cmd_parser() = default;

        ~cmd_parser() = default;

        int parse(int argc, char **argv, mstd::hash_table<mstd::string> &ht, bool allow_unknown = false) {
            for (int i = 1; i < argc; i++) {
                mstd::string s = argv[i];
                mstd::string type;
                if (!ht.get(s, &type) && !allow_unknown) {
                    std::cout << "Unknown key: " << s << std::endl;
                    return UNKNOWN_ARG;
                }

                if (type == "<none>") {
                    _unaries.add(s);
                } else if (type == "<i>") {
                    if (i + 1 >= argc) {
                        return WRONG_FORMAT;
                    } else {
                        _i_args.put(s, atoi(argv[++i]));
                    }
                } else if (type == "<s>") {
                    if (i + 1 >= argc) {
                        return WRONG_FORMAT;
                    } else {
                        _s_args.put(s, argv[++i]);
                    }
                } else {
                    return WRONG_INPUT;
                }
            }

            return SUCCESS;
        }

        bool get_string(mstd::string key, mstd::string *val) {
            return _s_args.get(key, val);
        }

        bool get_int(mstd::string key, int *val) {
            return _i_args.get(key, val);
        }

        bool is_set(mstd::string key) {
            return _unaries.in(key);
        }
    };
}
#endif //TRIES_CMD_PARSER_H
