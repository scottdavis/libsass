#define SASS_INTERFACE

#include "sass.h"
#include <stdbool.h>
#include "sass2scss.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SASS_STYLE_NESTED     0
#define SASS_STYLE_EXPANDED   1
#define SASS_STYLE_COMPACT    2
#define SASS_STYLE_COMPRESSED 3

// Please ensure there are no null values.
// Thar be dragons.
struct sass_options {
  // Output style for the generated css code
  // A value from above SASS_STYLE_* constants
  int output_style;
  // If you want inline source comments
  bool source_comments;
  // Path to source map file
  // Enables the source map generating
  // Used to create sourceMappingUrl
  const char* source_map_file;
  // Disable sourceMappingUrl in css output
  bool omit_source_map_url;
  // Colon-separated list of paths
  // Semicolon-separated on Windows
  const char* include_paths;
  // For the image-url Sass function
  const char* image_path;
  // Precision for outputting fractional numbers
  int precision;
};

struct sass_context {
  const char* input_path;
  const char* output_path;
  const char* source_string;
  char* output_string;
  char* source_map_string;
  struct sass_options options;
  int error_status;
  char* error_message;
  struct Sass_C_Function_Descriptor* c_functions;
  char** included_files;
  int num_included_files;
};

struct sass_file_context {
  const char* input_path;
  const char* output_path;
  char* output_string;
  char* source_map_string;
  struct sass_options options;
  int error_status;
  char* error_message;
  struct Sass_C_Function_Descriptor* c_functions;
  char** included_files;
  int num_included_files;
};

struct sass_folder_context {
  const char* search_path;
  const char* output_path;
  struct sass_options options;
  int error_status;
  char* error_message;
  struct Sass_C_Function_Descriptor* c_functions;
  char** included_files;
  int num_included_files;
};

struct sass_context*        sass_new_context        (void);
struct sass_file_context*   sass_new_file_context   (void);
struct sass_folder_context* sass_new_folder_context (void);

void sass_free_context        (struct sass_context* ctx);
void sass_free_file_context   (struct sass_file_context* ctx);
void sass_free_folder_context (struct sass_folder_context* ctx);

int sass_compile            (struct sass_context* ctx);
int sass_compile_file       (struct sass_file_context* ctx);
int sass_compile_folder     (struct sass_folder_context* ctx);

#ifdef __cplusplus
}
#endif
