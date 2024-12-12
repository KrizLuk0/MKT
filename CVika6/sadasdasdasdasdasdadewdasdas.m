close all
clear
Nsym=1000
Samples_per_symbol=4;
Symbs=randsrc(1,Nsym,[1 -1 +3 -3])+j*randsrc(1,Nsym,[1 -1 +3 -3]);
figure
plot(Symbs, 'o')
scatterplot(Symbs)
h=rcosine(1,Samples_per_symbol,'sqrt',0.3,5)
figure
stem(h)
SymbsI=real(Symbs); SymbsQ=imag(Symbs);
SymbsIUp=upsample(SymbsI,Samples_per_symbol); SymbsQUp=upsample(SymbsQ,Samples_per_symbol);
figure;stem(SymbsIUp)
SymsIf=filter(h,1,SymbsIUp);
SymsQf=filter(h,1,SymbsQUp);
figure;
s=SymsIf+j*SymsQf;
plot(s)
hold on
plot(s((length(h)-1)/2+1:Samples_per_symbol:end),'.r')
figure;
stem(SymsIf)
r=s;


% Prijimac:
RecI=filter(h,1,real(r));
RecQ=filter(h,1,imag(r));
RecSyms=RecI+j*RecQ;
figure;
plot(RecSyms)
zpozdeni=2*(length(h)-1)/2;
RecSymsD=RecSyms(zpozdeni+1:Samples_per_symbol:end);
hold on
plot(RecSymsD,'r.')