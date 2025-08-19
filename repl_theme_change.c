#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *type;
    char *foreground;
    char *background;
    int bold;
    int underline;
} ThemeElement;

// Helper function to extract attribute value
char *get_attribute(const char *attr_str, const char *attr_name) {
    char search[64];
    snprintf(search, sizeof(search), "%s=\"", attr_name);
    const char *p = strstr(attr_str, search);
    if (!p) return NULL;
    p += strlen(search);
    const char *end = strchr(p, '"');
    if (!end) return NULL;
    int len = end - p;
    char *val = (char *)malloc(len + 1); // Explicit cast
    if (val) {
        strncpy(val, p, len);
        val[len] = '\0';
    }
    return val;
}

// Parse XML to ThemeElements
ThemeElement *parse_repl_theme(const char *xml, int *num_elements) {
    *num_elements = 0;
    ThemeElement *elements = NULL;
    const char *p = xml;
    while ((p = strstr(p, "<element")) != NULL) {
        p += strlen("<element");
        while (*p == ' ' || *p == '\t' || *p == '\n') p++;
        const char *end = strstr(p, "/>");
        if (!end) break;
        int attr_len = end - p;
        char *attr_str = (char *)malloc(attr_len + 1); // Explicit cast
        if (!attr_str) break;
        strncpy(attr_str, p, attr_len);
        attr_str[attr_len] = '\0';
        p = end + 2;

        ThemeElement elem;
        memset(&elem, 0, sizeof(elem));

        elem.type = get_attribute(attr_str, "type");
        elem.foreground = get_attribute(attr_str, "foreground");
        elem.background = get_attribute(attr_str, "background");
        char *bold_str = get_attribute(attr_str, "bold");
        elem.bold = bold_str && strcmp(bold_str, "true") == 0;
        free(bold_str);
        char *underline_str = get_attribute(attr_str, "underline");
        elem.underline = underline_str && strcmp(underline_str, "true") == 0;
        free(underline_str);

        if (elem.type && elem.foreground && elem.background) {
            elements = (ThemeElement *)realloc(elements, (*num_elements + 1) * sizeof(ThemeElement)); // Explicit cast
            if (!elements) {
                free(elem.type);
                free(elem.foreground);
                free(elem.background);
                free(attr_str);
                break;
            }
            elements[*num_elements] = elem;
            (*num_elements)++;
        } else {
            free(elem.type);
            free(elem.foreground);
            free(elem.background);
        }

        free(attr_str);
    }
    return elements;
}

// Generate XML from ThemeElements
char *generate_repl_theme(const ThemeElement *elements, int num_elements) {
    char *xml = (char *)malloc(4096); // Explicit cast, assume sufficient size
    if (!xml) return NULL;
    strcpy(xml, "<repl_theme>\n");
    for (int i = 0; i < num_elements; i++) {
        char buf[512];
        snprintf(buf, sizeof(buf), "  <element type=\"%s\" foreground=\"%s\" background=\"%s\" bold=\"%s\" underline=\"%s\"/>\n",
                 elements[i].type ? elements[i].type : "",
                 elements[i].foreground ? elements[i].foreground : "",
                 elements[i].background ? elements[i].background : "",
                 elements[i].bold ? "true" : "false",
                 elements[i].underline ? "true" : "false");
        strcat(xml, buf);
    }
    strcat(xml, "</repl_theme>\n");
    return xml;
}

// Free ThemeElements
void free_theme(ThemeElement *elements, int num_elements) {
    for (int i = 0; i < num_elements; i++) {
        free(elements[i].type);
        free(elements[i].foreground);
        free(elements[i].background);
    }
    free(elements);
}

// Example usage
int main() {
    const char *xml = "<repl_theme>\n"
                      "  <element type=\"number\" foreground=\"blue\" background=\"default\" bold=\"false\" underline=\"false\"/>\n"
                      "  <element type=\"operator\" foreground=\"magenta\" background=\"default\" bold=\"true\" underline=\"false\"/>\n"
                      "</repl_theme>\n";

    int num;
    ThemeElement *elements = parse_repl_theme(xml, &num);

    printf("Parsed %d elements:\n", num);
    for (int i = 0; i < num; i++) {
        printf("Type: %s, FG: %s, BG: %s, Bold: %d, Underline: %d\n",
               elements[i].type, elements[i].foreground, elements[i].background,
               elements[i].bold, elements[i].underline);
    }

    char *generated = generate_repl_theme(elements, num);
    printf("\nGenerated XML:\n%s", generated);

    free_theme(elements, num);
    free(generated);

    return 0;
}

