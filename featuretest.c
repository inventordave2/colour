#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./../regex_w/wregex.h" // Werner Stoop's regex_w library header

// Define history structure: dynamic array of strings
typedef struct {
    char **entries;   // Array of strings
    size_t size;      // Current number of entries
    size_t capacity;  // Allocated capacity
} History;

// Initialize history
void init_history(History *hist) {
    hist->size = 0;
    hist->capacity = 16;
    hist->entries = (char **)malloc(hist->capacity * sizeof(char *));
    if (!hist->entries) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < hist->capacity; i++) {
        hist->entries[i] = NULL;
    }
}

// Free history
void free_history(History *hist) {
    for (size_t i = 0; i < hist->size; i++) {
        free(hist->entries[i]);
        hist->entries[i] = NULL;
    }
    free(hist->entries);
    hist->entries = NULL;
    hist->size = 0;
    hist->capacity = 0;
}

// Add entry to history
int add_to_history(History *hist, const char *entry) {
    if (!entry || !*entry) return -1;
    if (hist->size >= hist->capacity) {
        size_t new_capacity = hist->capacity ? hist->capacity * 2 : 16;
        char **new_entries = (char **)realloc(hist->entries, new_capacity * sizeof(char *));
        if (!new_entries) {
            perror("realloc failed");
            return -1;
        }
        hist->entries = new_entries;
        hist->capacity = new_capacity;
        for (size_t i = hist->size; i < hist->capacity; i++) {
            hist->entries[i] = NULL;
        }
    }
    hist->entries[hist->size] = strdup(entry);
    if (!hist->entries[hist->size]) {
        perror("strdup failed");
        return -1;
    }
    hist->size++;
    return 0;
}

// Search history using regex_w (case-insensitive, returns all matches)
size_t search_history_all(const History *hist, const char *pattern, char ***results) {
    if (!pattern || !*pattern) return 0;

    // Compile regex with case-insensitive flag (\i)
    char *case_insensitive_pattern = malloc(strlen(pattern) + 3);
    if (!case_insensitive_pattern) {
        perror("malloc failed");
        return 0;
    }
    sprintf(case_insensitive_pattern, "\\i%s", pattern); // Prepend \i for case-insensitivity

    wregex_t *regex;
    int err, err_pos;
    regex = wrx_comp(case_insensitive_pattern, &err, &err_pos);
    free(case_insensitive_pattern);
    if (!regex) {
        fprintf(stderr, "Regex compilation failed: %s\n", wrx_error(err));
        return 0;
    }

    // Allocate results array
    size_t match_capacity = 16;
    size_t match_count = 0;
    *results = (char **)malloc(match_capacity * sizeof(char *));
    if (!*results) {
        perror("malloc failed");
        wrx_free(regex);
        return 0;
    }

    // Search history entries
    for (size_t i = hist->size; i-- > 0;) {
        int ret = wrx_exec(regex, hist->entries[i], NULL);
        if (ret == 1) { // Match found
            if (match_count >= match_capacity) {
                match_capacity *= 2;
                char **new_results = (char **)realloc(*results, match_capacity * sizeof(char *));
                if (!new_results) {
                    perror("realloc failed");
                    free(*results);
                    *results = NULL;
                    wrx_free(regex);
                    return match_count;
                }
                *results = new_results;
            }
            (*results)[match_count++] = hist->entries[i];
        } else if (ret < 0) {
            fprintf(stderr, "Regex execution error: %s\n", wrx_error(ret));
        }
    }

    wrx_free(regex);
    return match_count;
}

// List all history entries
void list_history(const History *hist) {
    if (hist->size == 0) {
        printf("History is empty\n");
        return;
    }
    for (size_t i = 0; i < hist->size; i++) {
        printf("%zu: %s\n", i + 1, hist->entries[i]);
    }
}

// History manager subroutine
void history_manager(const char *action, const char *arg) {
    static History hist;
    static int initialized = 0;
    if (!initialized) {
        init_history(&hist);
        initialized = 1;
    }

    if (!action) {
        printf("Error: No action specified\n");
        return;
    }

    if (strcmp(action, "add") == 0) {
        if (!arg) {
            printf("Error: No entry provided for add\n");
            return;
        }
        if (add_to_history(&hist, arg) == 0) {
            printf("Added: %s\n", arg);
        }
    } else if (strcmp(action, "search") == 0) {
        if (!arg) {
            printf("Error: No pattern provided for search\n");
            return;
        }
        char **results = NULL;
        size_t count = search_history_all(&hist, arg, &results);
        if (count > 0) {
            printf("Found %zu match(es) for pattern '%s':\n", count, arg);
            for (size_t i = 0; i < count; i++) {
                printf("  %s\n", results[i]);
            }
            free(results);
        } else {
            printf("No match for pattern '%s'\n", arg);
        }
    } else if (strcmp(action, "list") == 0) {
        list_history(&hist);
    } else if (strcmp(action, "clear") == 0) {
        free_history(&hist);
        init_history(&hist);
        printf("History cleared\n");
    } else {
        printf("Unknown action: %s\n", action);
    }
}

// Main for demonstration
int main() {
    history_manager("add", "echo Hello World");
    history_manager("add", "ls -la");
    history_manager("add", "grep 'error' log.txt");
    history_manager("add", "ECHO Goodbye WORLD");
    history_manager("list", NULL);
    history_manager("search", "echo.*world"); // Regex pattern
    history_manager("search", "grep");        // Simple pattern
    history_manager("search", NULL);          // Test invalid input
    history_manager("clear", NULL);
    history_manager("list", NULL);
    return 0;
}

