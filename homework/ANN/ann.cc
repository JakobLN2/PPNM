#include"ann.h"

double ann::eval(double x) const {
    double res = 0;
    for(int i = 0; i < n; ++i) res += F_neuron(x,P.getRow(i));
    return res;
}

vector ann::eval2(double x) const {
    // I really dont want to add logic to make this easier, just kill the program if it does not go as i want it to.
    if(act != "gaussian wavelet") throw std::logic_error("expanded eval is only implemented for gaussian wavelet activation function");
    vector res(4);
    res[0] = eval(x);
    double a,b,w,u;
    for(int i = 0; i < P.nrows; i++) {
        a = P(i,0); b = P(i,1); w = P(i,2);
        u = (x-a/b);
        res[1] += w/b*(1-2*u*u)*std::exp(-u*u);
        res[2] += w/b/b*2*u*(2*u*u-3)*std::exp(-u*u);
        res[3] += -0.5*w*b*(std::exp(-u*u) - std::exp(-a*a/b/b));
    }
    return res;
}

void ann::train(const vector& x, const vector& y) {
    std::function<double(vector)> F_cost = [&](vector p){
        double cost = 0;
        for(int i = 0; i < x.size ; ++i) {
            double res = 0;
            for(int j = 0; j < n; ++j) res += F_neuron(x[i], vector({p[3*j],p[3*j+1],p[3*j+2]}));
            cost += std::pow(res - y[i],2);
        }
        return cost;
    };
    int epochs = 10000;
    int starts = 3;
    std::cerr << "Training network with " << n << " neurons for " << x.size << " datapoints\nEpochs: " << epochs << ", Random start locations: " << starts <<"\n";
    
    std::uniform_real_distribution<double> unif(-1,1);
    std::default_random_engine re(5);
    
    vector px(3*n);
    for(int i = 0; i < 3*n ; ++i) px[i] = unif(re)*2; //Random start guess
    reshape(px,n,3).print("p0 = ",std::cerr);
    std::cerr << "Initial cost: " << F_cost(px) << "\n";
    
    double cost_min = F_cost(px);
    vector p_opt = px.copy();
    int epoch = 0, epoch_best = 0, guess_best = 0;

    for(int i = 0; i < starts ; ++i) {
        if(i > 0) for(int i = 0; i < 3*n ; ++i) px[i] = unif(re)*2; //New random start guess
        do {
            vector gp = gradient(x,y,px);
            px -= gp/128.0;
            double cost = F_cost(px);
            if(cost < cost_min) {
                p_opt = px.copy();
                cost_min = cost;
                epoch_best = epoch + 1;
                guess_best = i+1;
            }
            epoch++;
        } while(epoch < 10000);
        epoch = 0;
    }

    std::cerr << "Training complete, best cost: " << F_cost(p_opt) << " at epoch " << epoch_best << " for start location " << guess_best << "\n";


    // std::uniform_real_distribution<double> unif(-1,1);
    // std::default_random_engine re(5);
    
    // vector p0(3*n);
    // for(int i = 0; i < 3*n ; ++i) p0[i] = unif(re)*64; //Random start guess
    // reshape(p0,n,3).print("p0 = ",std::cerr);
    // std::cerr << "Initial cost: " << F_cost(p0) << "\n";

    // std::tuple<vector,int> res = newton(F_cost,p0,1e-3,1);
    // vector p_opt = std::get<0>(res);
    // int N = std::get<1>(res);
    
    // std::cerr << "Training complete in " << N << " iterations\nFinal cost: " << F_cost(p_opt) << "\n";
    
    P = reshape(p_opt, n, 3);
    P.print("P = ", std::cerr);
}

vector ann::gradient(const vector& x, const vector& y, const vector& p) {
    vector gp(p.size);
    for(int i = 0; i < p.size; i += 3) {
        vector pj({p[i],p[i+1],p[i+2]});
        for(int k = 0; k < x.size; ++k) {
            gp[i] += dL_da(x[k],y[k],pj);
            gp[i+1] += dL_db(x[k],y[k],pj);
            gp[i+2] += dL_dw(x[k],y[k],pj);
        }
    }
    gp.normalize();
    return gp;
}