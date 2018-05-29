/* HEADER FILE: SortMarks.h */

#ifndef SORTMARKS_H
#define SORTMARKS_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "Marks.h"

class SortMarks
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <Marks> marks;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortMarks(std::vector <Marks> &, std::string);
    static bool cmp_by_application_id(Marks &, Marks &);
    static bool cmp_by_confirmed(Marks &, Marks &);
    static bool cmp_by_created_at(Marks &, Marks &);
    static bool cmp_by_details(Marks &, Marks &);
    static bool cmp_by_diameter(Marks &, Marks &);
    static bool cmp_by_id(Marks &, Marks &);
    static bool cmp_by_image_id(Marks &, Marks &);
    static bool cmp_by_image_user_id(Marks &, Marks &);
    static bool cmp_by_machine_mark_id(Marks &, Marks &);
    static bool cmp_by_score(Marks &, Marks &);
    static bool cmp_by_shared_mark_id(Marks &, Marks &);
    static bool cmp_by_sub_type(Marks &, Marks &);
    static bool cmp_by_submit_time(Marks &, Marks &);
    static bool cmp_by_type(Marks &, Marks &);
    static bool cmp_by_updated_at(Marks &, Marks &);
    static bool cmp_by_user_id(Marks &, Marks &);
    static bool cmp_by_x(Marks &, Marks &);
    static bool cmp_by_y(Marks &, Marks &);
    int GetFieldValue();
    std::vector <Marks> GetMarks();
    void arrange();
};

#endif
