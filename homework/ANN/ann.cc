#include"ann.h"

double ann::eval(double x) const {
    double res = 0;
    for(int i = 0; i < n; ++i) res += F_neuron(x,P.getRow(i));
    return res;
}

vector ann::eval_derivs(double x) const {
    // I really dont want to add logic to make this easier, just kill the program if it does not go as i want it to.
    if(act != "gaussian wavelet") throw std::logic_error("expanded eval is only implemented for gaussian wavelet activation function");
    vector res(4);
    res[0] = eval(x);
    double a,b,w,u,euu;
    for(int i = 0; i < n; i++) {
        a = P(i,0); b = P(i,1); w = P(i,2);
        u = (x-a)/b;
        euu = std::exp(-u*u);
        res[1] += w/b*(1-2*u*u)*euu;
        res[2] += w/b/b*2*u*(2*u*u-3)*euu;
        res[3] += -0.5*w*b*(euu - std::exp(-a*a/b/b));
    }
    return res;
}

void ann::train(const vector& x, const vector& y, double acc) {
    std::function<double(vector)> F_cost = [&](vector p){
        double cost = 0;
        for(int i = 0; i < x.size ; ++i) {
            double res = 0;
            for(int j = 0; j < n; ++j) res += F_neuron(x[i], vector({p[3*j],p[3*j+1],p[3*j+2]}));
            cost += std::pow(res - y[i],2);
        }
        return cost;
    };
    
    int epochs = 15000; //Number of iterations to calculate the gradient
    int starts = 3; //Number of random start guesses for weights
    std::cerr << "Training network with " << n << " neurons for " << x.size << " datapoints\nEpochs: " << epochs << ", Random start locations: " << starts <<"\n";
    
    std::uniform_real_distribution<double> unif(-1,1);
    std::default_random_engine re(0);
    
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
                epoch_best = epoch + 1;
                guess_best = i+1;
                if(cost_min - cost < acc) break; //Our improvement is extremely marginal, probably very close to the minimum. 
                //I do not have adaptive step sizes so we'll probably start oscillating around the minimum which this hopefully avoids
                cost_min = cost;
            }
            epoch++;
        } while(epoch < epochs);

        epoch = 0;
    }

    std::cerr << "Training complete: best cost: " << F_cost(p_opt) << " at epoch " << epoch_best << " for start location " << guess_best << "\n";

    P = reshape(p_opt, n, 3);
    P.print("P = ", std::cerr);
}

vector ann::gradient(const vector& x, const vector& y, const vector& p) {
    vector ak(x.size);
    for(int k = 0; k < x.size; ++k) {
        double a = -y[k];
        for(int i = 0; i < n; ++i) a += F_act((x[k] - p[3*i])/p[3*i+1])*p[3*i+2];
        ak[k] = a;
    }
    
    vector gp(p.size);
    for(int i = 0; i < n; ++i) {
        vector pj({p[3*i],p[3*i+1],p[3*i+2]});
        for(int k = 0; k < x.size; ++k) {
            gp[3*i]   += dL_da(x[k],ak[k],pj);
            gp[3*i+1] += dL_db(x[k],ak[k],pj);
            gp[3*i+2] += dL_dw(x[k],ak[k],pj);
        }
    }
    gp.normalize();
    return gp;
}