#include "User.h"
#include "RecommendationSystem.h"

//
// Created by idodo on 25/07/2024.
//
void User::add_movie_to_user(const std::string &name, int year,
                       const std::vector<double> &features,
                       double rate)
{
    sp_movie p_movie =  _s_rs->add_movie_to_rs(name,year,features);
    _my_ratings[p_movie] = rate;
}
sp_movie User:: get_rs_recommendation_by_content() const
{return _s_rs->recommend_by_content(*this);}

sp_movie User:: get_rs_recommendation_by_cf(int k) const
{return _s_rs->recommend_by_cf(*this,k);}

double User::get_rs_prediction_score_for_movie(const std::string& name, int
year,
                                         int k) const
{return _s_rs->predict_movie_score(*this,std::make_shared<Movie>
        (name, year),k);}

