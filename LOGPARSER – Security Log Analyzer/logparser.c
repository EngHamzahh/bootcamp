
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 512U

static int read_line(FILE *file, char **line, size_t *capacity)
{
    char chunk[CHUNK_SIZE];
    size_t length = 0U;

    if (*line == NULL || *capacity == 0U) {
        *capacity = CHUNK_SIZE;
        *line = malloc(*capacity);

        if (*line == NULL)
            return -1;
    }

    (*line)[0] = '\0';

    while (fgets(chunk, (int)sizeof chunk, file) != NULL) {
        size_t chunk_length = strlen(chunk);
        size_t required = length + chunk_length + 1U;

        if (required > *capacity) {
            size_t new_capacity = *capacity;

            while (new_capacity < required) {
                if (new_capacity > ((size_t)-1) / 2U)
                    return -1;

                new_capacity *= 2U;
            }

            char *new_line = realloc(*line, new_capacity);

            if (new_line == NULL)
                return -1;

            *line = new_line;
            *capacity = new_capacity;
        }

        memcpy(*line + length, chunk, chunk_length + 1U);
        length += chunk_length;

        if (chunk_length > 0U &&
            chunk[chunk_length - 1U] == '\n')
            return 1;
    }

    if (ferror(file))
        return -1;

    return (length > 0U) ? 1 : 0;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t capacity = 0U;
    size_t line_number = 0U;
    size_t alert_count = 0U;
    int read_status;

    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <log_file> <keyword>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[2][0] == '\0') {
        fprintf(stderr, "Error: Empty keyword.\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("LOGPARSER: Cannot open file");
        return EXIT_FAILURE;
    }

    printf("\n========== LOGPARSER ==========\n");
    printf("Log file : %s\n", argv[1]);
    printf("Keyword  : %s\n", argv[2]);
    printf("===============================\n\n");

    while ((read_status =
            read_line(file, &line, &capacity)) == 1) {

        line_number++;

        if (strstr(line, argv[2]) != NULL) {
            alert_count++;

            printf("[ALERT] Line %zu: %s",
                   line_number, line);

            size_t len = strlen(line);

            if (len == 0U || line[len - 1U] != '\n')
                putchar('\n');
        }
    }

    if (read_status == -1) {
        fprintf(stderr, "Error reading log file.\n");
        free(line);
        fclose(file);
        return EXIT_FAILURE;
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    printf("\n========== ANALYSIS SUMMARY ==========\n");
    printf("Total lines scanned : %zu\n", line_number);
    printf("Keyword searched    : %s\n", argv[2]);
    printf("Alerts detected     : %zu\n", alert_count);
    printf("======================================\n");

    return EXIT_SUCCESS;
}
