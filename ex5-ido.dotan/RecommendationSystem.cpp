//
// Created by idodo on 25/07/2024.
//
#include "RecommendationSystem.h"
#include <cmath>
#include <algorithm>
#include "set"

sp_movie RecommendationSystem:: add_movie_to_rs(const std::string& name,int
year
        ,const std::vector<double>& features)
{
    sp_movie p_movie = std::make_shared<Movie>(name,year);
    _movie_list[p_movie] = features;
    return p_movie;
}
double RecommendationSystem::calculate_norm(const std::vector<double>& v)
{
    size_t v_size = v.size();
    double norm = 0;
    for (size_t i = 0; i <v_size;i++)
    {
        norm += pow(v[i],2);
    }
    norm = sqrt(norm);
    return norm;
}
double RecommendationSystem::inner_product(const std::vector<double>& v1,
                                           const std::vector<double>& v2)
{
    size_t v_size = v1.size();
    double inner_prod = 0;
    for (size_t i = 0; i <v_size;i++)
    {
        inner_prod += v1[i] * v2[i];
    }
    return inner_prod;
}
double RecommendationSystem::calculate_angle(const std::vector<double>& v1,
                                            const std::vector<double>& v2)
{
   double angle = inner_product(v1,v2);
   angle /= (calculate_norm(v1) * calculate_norm(v2));
    return angle;

}
sp_movie RecommendationSystem:: recommend_by_content(const User& user)
{
    double avg = 0;
    int count = 0;
    size_t v_size;
    for (const auto& p_movie:user.get_ranks())
    {
        avg = avg+p_movie.second;
        count++;
        v_size = _movie_list[p_movie.first].size();
    }
    if (count)
    {
        avg /= count;
    }

    std::vector<double> pre_vec(v_size,0);
    for (const auto& p_movie:_movie_list)
    {
        auto it = user.get_ranks().find(p_movie.first);
        if (it != user.get_ranks().end())
        {
            double norm_val = it->second-avg;
            for (size_t j = 0; j < v_size; j++)
            {
                pre_vec[j] += norm_val*_movie_list[p_movie.first][j];
            }
        }
    }
    double max_imag = -1;
    sp_movie rec;
    for (const auto& p_movie:_movie_list)
    {
        auto it = user.get_ranks().find(p_movie.first);
        if (it == user.get_ranks().end())
        {
            double angle = calculate_angle(pre_vec,p_movie.second);
            if (angle > max_imag)
            {
                max_imag = angle;
                rec = p_movie.first;
            }
        }
    }
    return rec;
}
double RecommendationSystem::predict_movie_score(const User &user,
                                                 const sp_movie &movie,
                                                 int k)
{
    std::vector<double> feat = _movie_list[movie];
    std::vector<std::pair<sp_movie, double>> img_list;
    for (auto const& p_movie:user.get_ranks())
    {
        double img = calculate_angle(feat,_movie_list[p_movie.first]);
        img_list.emplace_back(p_movie.first,img);
    }
    std::sort(img_list.begin(), img_list.end(),
              [](const auto& a, const auto& b)
              {
        return a.second > b.second;
    });

    img_list.resize(k);
    double predict = 0;
    double total_img = 0;
    for (int i = 0; i < k; i++)
    {
        double curr_imag = img_list[i].second;
        total_img += curr_imag;
        double curr_rating =
                user.get_ranks().find(img_list[i].first)->second;
        predict += curr_imag*curr_rating;
    }
    predict /= total_img;
    return predict;

}
sp_movie RecommendationSystem::recommend_by_cf(const User &user, int k)
{
    double curr_predict = 0;
    sp_movie rec;
    for (const auto& p_movie:_movie_list)
    {
        double curr = predict_movie_score(user,p_movie.first,k);
        if (curr > curr_predict)
        {
            curr_predict = curr;
            rec = p_movie.first;
        }
    }
    return rec;
}
sp_movie RecommendationSystem::get_movie(const std::string &name, int year)
{
    sp_movie p_movie = std::make_shared<Movie>(name, year);
    auto it = _movie_list.find(p_movie);
    if (it != _movie_list.end()) {
        return it->first;
    }
    return nullptr;
}
std::ostream& operator<<(std::ostream& os,const
RecommendationSystem& rs)
{
    for (const auto& p_movie:rs._movie_list)
    {
        os << *p_movie.first;
    }
    return os;
}
