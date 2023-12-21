/*
 *  @author: dwclake
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>
#include <string.h>
#include "../helpers/position.h"
#include "../helpers/vector.h"
#include "../helpers/buffer.h"

struct Compiler;

/* Scanner messages */
enum {
    SCANNER_FILE_SCANNED_OK,
    SCANER_FAILED_WITH_ERRORS
};

/* Token types */
enum {
    IDENTIFIER,
    KEYWORD,
    SYMBOL,
    INTEGER,
    FLOAT,
    STRING,
    REGEX,
    COMMENT
};

/* Token structure */
struct Token {
    int type;
    int flags;

    /* Data for various tokens */
    union {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };

    bool whitespace;
    const char* between_brackets;

    struct Pos pos;
};

/* State for the scanning process */
struct Scanner {
    struct Pos pos;
    struct Vector* tokens;
    struct Compiler* compiler;

    int current_expression_count;
    struct Buffer* parenthesis;
    struct ScannerFunctions* function;

    void* private_data;
};

/* Fuction types to abstract some scanning functionality */
typedef char (*SCANNER_NEXT_CHAR)(struct Scanner* process);
typedef char (*SCANNER_PEEK_CHAR)(struct Scanner* process);
typedef void (*SCANNER_PUSH_CHAR)(struct Scanner* process, char c);

/* Struct representing the scanning functions used by the scan process */
struct ScannerFunctions {
    SCANNER_NEXT_CHAR next_char;
    SCANNER_PEEK_CHAR peek_char;
    SCANNER_PUSH_CHAR push_char;
};

/* Scans the file in the scan process
 * @param process The scanner process to be used in scanning
 * @return A integer signaling the result of the scan
 */
int scan(struct Scanner* process);

/* Creates a new scanner process
 * @param compiler The compiler process the scanner will belong to
 * @param functions The functions the scanner will use
 * @param private_data The private data only the caller understands
 * @return A pointer to a new Scanner or NULL
 */
struct Scanner* create_scanner(struct Compiler* compiler, 
                               struct ScannerFunctions* functions, 
                               void* private_data
                               );

/* Frees a scanner process from memory
 * @param process The scanner process to be freed
 * @return void
 */
void free_scanner(struct Scanner* process);

/* Retrieves scanner's private data
 * @param process The scanner whose private data is being retrieved
 * @return void
 */
void* scanner_private(struct Scanner* process);

/* Retrieves scanner's tokens vector
 * @param process The scanner whose tokens vector is being retrieved
 * @return Pointer to the Token Vector
 */
struct Vector* scanner_tokens(struct Scanner* process);

/* Retrieves the next char from the scanner
 * @param process The process to retrieve the next char from
 * @return The next char in the file buffer
 */
char scanner_next_char(struct Scanner* process);

/* Retrieves the next char from the scanner preserving the file stream
 * @param process The process to peek the next char from
 * @return The next char in the file buffer
 */
char scanner_peek_char(struct Scanner* process);

/* Pushes c onto the file buffer
 * @param process The scanner containing the file buffer to push the char onto
 * @param c The char to push onto the file buffer
 * @return void
 */
void scanner_push_char(struct Scanner* process, char c);

#endif
