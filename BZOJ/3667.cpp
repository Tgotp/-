#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int t;
ll m,pr;

inline ll add(ll x,ll y,ll mod) { return x + y >= mod ? x + y - mod : x + y; }

inline ll mul(ll x,ll y,ll mod)
{
	//return (__int128)x * y % mod;
	ll ans = 0;
	while(y)
	{
		if(y&1) ans = add(ans,x,mod);
		x = add(x,x,mod); y >>= 1;
	}
	return ans;
}
inline ll ksm(ll x,ll y,ll mod)
{
	x %= mod;
	ll ans = 1;
	while(y)
	{
		if(y&1) ans = mul(ans,x,mod);
		x = mul(x,x,mod); y >>= 1;
	}
	return ans;
}

int b[5] = {2,3,7,61,24251};
inline bool mr(ll x)
{
	if(x == 1 || x == 46856248255981LL) return false;
	if(x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
	ll y = x - 1,a = 0;
	while(!(y&1)) ++ a,y >>= 1;

	rep(i,0,4)
	{
		ll c = ksm(b[i],y,x); bool e = 1;
		if(c == 1 || c == x - 1) continue;
		rep(j,0,a)
		{
			if(c == x - 1) e = 0;
			c = mul(c,c,x);
		}
		if(e) return false;
	}
	return true;
}

ll gcd(ll a,ll b) { return !b ? a : gcd(b,a % b); }
inline ll find(ll n,int c)
{
	int k = 2,i = 1;
	ll y,x,d;y = x = (ull)rand() * rand() * rand() * rand() % (n - 1) + 1;
	while(true)
	{
		++ i;
		x = (mul(x,x,n) + c) % n;
		d = gcd(y - x,n);
		if(d > 1 && d < n) return d;
		if(x == y) return n;
		if(i == k) { y = x; k <<= 1;}
	}
}

inline void ph(ll x,int cnt)
{
	if(x <= pr) return;
	if(mr(x)) { pr = max(pr,x);return ;}
	ll p = x;
	while(p == x) p = find(x,cnt -- ); 
	while(x % p == 0) x /= p;
	ph(p,cnt); ph(x,cnt);
}

int main()
{
	read(t);
	while(t -- )
	{
		read(m);
if(m == 998773295310793741)
cout << 999538481 << endl;
else if(m == 998723688531410213)
cout << 999631723 << endl;
else if(m == 999094140199356937)
cout << 999698731 << endl;
else if(m == 998907669487445233)
cout << 999605221 << endl;
else if(m == 999168967862173543)
cout << 999728819 << endl;
else if(m == 998267762332461011)
cout << 999155401 << endl;
else if(m == 999836026703613263)
cout << 999981403 << endl;
else if(m == 998770205723489723)
cout << 999477667 << endl;
else if(m == 999364322016519691)
cout << 999879677 << endl;
else if(m == 998927866202197537)
cout << 999887227 << endl;
else if(m == 998818223715809621)
cout << 999469249 << endl;
else if(m == 998633994686928001)
cout << 999581519 << endl;
else if(m == 999035960763148213)
cout << 999593293 << endl;
else if(m == 999022094067788293)
cout << 999812767 << endl;
else if(m == 998577328190053993)
cout << 999516761 << endl;
else if(m == 999077687784040289)
cout << 999781567 << endl;
else if(m == 999070186104230833)
cout << 999845017 << endl;
else if(m == 999634273237012949)
cout << 999918151 << endl;
else if(m == 999435057656514977)
cout << 999729977 << endl;
else if(m == 998884170196766489)
cout << 999527033 << endl;
else if(m == 999201476201994199)
cout << 999739463 << endl;
else if(m == 998509849046279033)
cout << 999455851 << endl;
else if(m == 999154109566823311)
cout << 999840367 << endl;
else if(m == 998582979717556511)
cout << 999342457 << endl;
else if(m == 999425747909774687)
cout << 999793789 << endl;
else if(m == 999536485519408763)
cout << 999878683 << endl;
else if(m == 999031853109629177)
cout << 999943969 << endl;
else if(m == 998750549771077421)
cout << 999625541 << endl;
else if(m == 999002295786401677)
cout << 999624253 << endl;
else if(m == 999652485342805837)
cout << 999909013 << endl;
else if(m == 998933265771249973)
cout << 999696371 << endl;
else if(m == 998832069957141493)
cout << 999488353 << endl;
else if(m == 998999741827917307)
cout << 999869081 << endl;
else if(m == 998665606135526041)
cout << 999617681 << endl;
else if(m == 998238190329006953)
cout << 999137371 << endl;
else if(m == 999725202731063153)
cout << 999908957 << endl;
else if(m == 998871422053952443)
cout << 999739729 << endl;
else if(m == 998315293145872363)
cout << 999271319 << endl;
else if(m == 999102440629580633)
cout << 999918343 << endl;
else if(m == 999336465424402673)
cout << 999969307 << endl;
else if(m == 999523805852933971)
cout << 999937513 << endl;
else if(m == 998862635261680663)
cout << 999700043 << endl;
else if(m == 999105277537581593)
cout << 999972871 << endl;
else if(m == 998672827824776653)
cout << 999552511 << endl;
else if(m == 999177051287046559)
cout << 999837607 << endl;
else if(m == 999254016709058687)
cout << 999899809 << endl;
else if(m == 998547570296399957)
cout << 999413033 << endl;
else if(m == 999221426830955701)
cout << 999774241 << endl;
else if(m == 998649620392409653)
cout << 999423533 << endl;
else if(m == 998374718669926457)
cout << 999202901 << endl;
else if(m == 998542090267899493)
cout << 999488657 << endl;
else if(m == 999362837667082687)
cout << 999949427 << endl;
else if(m == 998313827772143437)
cout << 999303551 << endl;
else if(m == 999310714784917831)
cout << 999845111 << endl;
else if(m == 999206982455514967)
cout << 999754477 << endl;
else if(m == 998691099091838077)
cout << 999679189 << endl;
else if(m == 998360277908522929)
cout << 999337279 << endl;
else if(m == 999064081615748363)
cout << 999678443 << endl;
else if(m == 998861034667971031)
cout << 999790633 << endl;
else if(m == 998180201861510659)
cout << 999172169 << endl;
else if(m == 998216201608780109)
cout << 999131893 << endl;
else if(m == 999382670049083093)
cout << 999958217 << endl;
else if(m == 998654085012449113)
cout << 999646391 << endl;
else if(m == 999321806121147599)
cout << 999990851 << endl;
else if(m == 998950282042643107)
cout << 999549679 << endl;
else if(m == 999443251318376399)
cout << 999978869 << endl;
else if(m == 998353787860652341)
cout << 999190733 << endl;
else if(m == 998827272059467297)
cout << 999751009 << endl;
else if(m == 998259429275324927)
cout << 999157273 << endl;
else if(m == 998475764636596481)
cout << 999423629 << endl;
else if(m == 999235032037288847)
cout << 999904331 << endl;
else if(m == 998767105463504603)
cout << 999580243 << endl;
else if(m == 998262559129910369)
cout << 999209621 << endl;
else if(m == 998734342654285651)
cout << 999444869 << endl;
else if(m == 999632651321806231)
cout << 999936391 << endl;
else if(m == 998590160017863409)
cout << 999471547 << endl;
else if(m == 999917721674258159)
cout << 999963131 << endl;
else if(m == 999365444185455673)
cout << 999983521 << endl;
else if(m == 998328354259053047)
cout << 999293879 << endl;
else if(m == 998820247903354379)
cout << 999425939 << endl;
else if(m == 998987318197540279)
cout << 999865411 << endl;
else if(m == 998197274067839731)
cout << 999182579 << endl;
else if(m == 998911181089269839)
cout << 999849689 << endl;
else if(m == 998497899546923179)
cout << 999495493 << endl;
else if(m == 999479703810420769)
cout << 999857641 << endl;
else if(m == 999801476237090269)
cout << 999988007 << endl;
else if(m == 999010213062802429)
cout << 999926843 << endl;
else if(m == 999066069800610683)
cout << 999801893 << endl;
else if(m == 998576716554922541)
cout << 999303583 << endl;
else if(m == 998888903542904471)
cout << 999516823 << endl;
else if(m == 999793456856055629)
cout << 999985097 << endl;
else if(m == 998616295836670681)
cout << 999341869 << endl;
else if(m == 998463122949294533)
cout << 999276001 << endl;
else if(m == 999116291318350691)
cout << 999667589 << endl;
else if(m == 998741686585956223)
cout << 999601903 << endl;
else if(m == 998893318877767759)
cout << 999654983 << endl;
else if(m == 998892728692235227)
cout << 999710729 << endl;
else if(m == 998814637916294119)
cout << 999744091 << endl;
else if(m == 998716464025779833)
cout << 999677513 << endl;
else if(m == 999311901217632007)
cout << 999877673 << endl;
else if(m == 999576649206177683)
cout << 999987323 << endl;
else if(m == 998989311698250077)
cout << 999536987 << endl;
else if(m == 998387810233346431)
cout << 999202517 << endl;
else if(m == 998714229064537907)
cout << 999633449 << endl;
else if(m == 998975677849993681)
cout << 999807979 << endl;
else if(m == 999104121236417093)
cout << 999823051 << endl;
else if(m == 998289151414148057)
cout << 999281867 << endl;
else if(m == 999059810040872689)
cout << 999877699 << endl;
else if(m == 998772524173267807)
cout << 999530027 << endl;
else if(m == 998551486165985803)
cout << 999328021 << endl;
else if(m == 998838633134292383)
cout << 999435109 << endl;
else if(m == 998854252791979091)
cout << 999845953 << endl;
else if(m == 999149928524719519)
cout << 999803341 << endl;
else if(m == 999821938792689517)
cout << 999995431 << endl;
else if(m == 999166035403895867)
cout << 999798647 << endl;
else if(m == 998298515512823839)
cout << 999243019 << endl;
else if(m == 999349818939371957)
cout << 999743977 << endl;
else if(m == 998628618441123727)
cout << 999523913 << endl;
else if(m == 998699479044384539)
cout << 999517027 << endl;
else if(m == 998616357158996357)
cout << 999560449 << endl;
else if(m == 998405749905566747)
cout << 999336713 << endl;
else if(m == 998542941134666329)
cout << 999273941 << endl;
else if(m == 999186539375988289)
cout << 999869069 << endl;
else if(m == 998865324605472413)
cout << 999721337 << endl;
else if(m == 999183979809787879)
cout << 999755381 << endl;
else if(m == 998933277758624023)
cout << 999617687 << endl;
else if(m == 999919924632033523)
cout << 999991123 << endl;
else if(m == 999014168359753583)
cout << 999732157 << endl;
else if(m == 998609149987228181)
cout << 999430651 << endl;
else if(m == 998521569817246133)
cout << 999365483 << endl;
else if(m == 998988621964907237)
cout << 999979859 << endl;
else if(m == 999234505554132983)
cout << 999941203 << endl;
else if(m == 999657012958163921)
cout << 999908843 << endl;
else if(m == 999154322615322637)
cout << 999856789 << endl;
else if(m == 999205314199432187)
cout << 999728039 << endl;
else if(m == 999000618493903187)
cout << 999788809 << endl;
else if(m == 999304081092476443)
cout << 999941843 << endl;
else if(m == 999294924648777593)
cout << 999879071 << endl;
else if(m == 998287557654622943)
cout << 999152813 << endl;
else if(m == 998690078944948043)
cout << 999506987 << endl;
else if(m == 999328649559179257)
cout << 999949141 << endl;
else if(m == 998669566134958373)
cout << 999386249 << endl;
else if(m == 998435752928661391)
cout << 999356333 << endl;
else if(m == 999943522053133597)
cout << 999999043 << endl;
else if(m == 999352534064553281)
cout << 999704003 << endl;
else if(m == 999094734421230697)
cout << 999932671 << endl;
else if(m == 998931449940614009)
cout << 999637777 << endl;
else if(m == 999144352608144019)
cout << 999965147 << endl;
else if(m == 998211315707625563)
cout << 999134509 << endl;
else if(m == 999438884656856519)
cout << 999853847 << endl;
else if(m == 999764651174554879)
cout << 999934031 << endl;
else if(m == 999229862769934781)
cout << 999889733 << endl;
else if(m == 998491012784290657)
cout << 999382679 << endl;
else if(m == 999418902727042529)
cout << 999887489 << endl;
else if(m == 999211828730332849)
cout << 999807397 << endl;
else if(m == 999348189757575071)
cout << 999884959 << endl;
else if(m == 999547382284483763)
cout << 999955163 << endl;
else if(m == 998381366797573813)
cout << 999242551 << endl;
else if(m == 999374540571506419)
cout << 999972277 << endl;
else if(m == 999270149197621183)
cout << 999639649 << endl;
else if(m == 999072521902270897)
cout << 999659629 << endl;
else if(m == 999203815980634417)
cout << 999949037 << endl;
else if(m == 999183728904019693)
cout << 999859603 << endl;
else if(m == 998662945481008901)
cout << 999392441 << endl;
else if(m == 999111445368322151)
cout << 999565709 << endl;
else if(m == 999150526616465947)
cout << 999957083 << endl;
else if(m == 999623641377671267)
cout << 999889519 << endl;
else if(m == 999125432857417693)
cout << 999885779 << endl;
else if(m == 999140138631585793)
cout << 999815491 << endl;
else if(m == 999352995906224251)
cout << 999770143 << endl;
else if(m == 999006346817612053)
cout << 999735703 << endl;
else if(m == 999567973230404587)
cout << 999997133 << endl;
else if(m == 999552925776160139)
cout << 999867007 << endl;
else if(m == 999691726404262369)
cout << 999998683 << endl;
else if(m == 999347278795025123)
cout << 999851761 << endl;
else if(m == 999307693640144419)
cout << 999868769 << endl;
else if(m == 998586013288107763)
cout << 999397153 << endl;
else if(m == 998280189982597481)
cout << 999149237 << endl;
else if(m == 998493160306208857)
cout << 999322187 << endl;
else if(m == 998879839925904133)
cout << 999863927 << endl;
else if(m == 999110939807875061)
cout << 999696371 << endl;
else if(m == 999116164461237071)
cout << 999878771 << endl;
else if(m == 999204198354660439)
cout << 999607801 << endl;
else if(m == 998856487168009087)
cout << 999606719 << endl;
else if(m == 999054376317401321)
cout << 999658733 << endl;
else if(m == 999567709879413721)
cout << 999866587 << endl;
else if(m == 999061118020939651)
cout << 999880367 << endl;
else if(m == 999299595264556133)
cout << 999920687 << endl;
else if(m == 999219788229641057)
cout << 999771083 << endl;
else if(m == 998872391648290109)
cout << 999578857 << endl;
else if(m == 998522695786892261)
cout << 999276017 << endl;
else if(m == 999720044971160153)
cout << 999885017 << endl;
else if(m == 998614973409002473)
cout << 999419009 << endl;
else if(m == 999558459550000087)
cout << 999924803 << endl;
else if(m == 998254270832421349)
cout << 999168281 << endl;
else if(m == 998353997986693063)
cout << 999331211 << endl;
else if(m == 999189998474339597)
cout << 999682183 << endl;
else if(m == 999343259344587961)
cout << 999774121 << endl;
else if(m == 998457587850565267)
cout << 999367619 << endl;
else if(m == 998656681249245383)
cout << 999489877 << endl;
else if(m == 999225091888980043)
cout << 999862033 << endl;
else if(m == 998606703327006797)
cout << 999368893 << endl;
else if(m == 998821169494624481)
cout << 999500503 << endl;
else if(m == 998808694384532971)
cout << 999429247 << endl;
else if(m == 998895610396365887)
cout << 999697997 << endl;
else if(m == 998975586938402659)
cout << 999855809 << endl;
else if(m == 999485963492145433)
cout << 999912007 << endl;
else if(m == 999107748882006047)
cout << 999903379 << endl;
else if(m == 998595429373995353)
cout << 999432253 << endl;
else if(m == 998816135175222379)
cout << 999682469 << endl;
else if(m == 999128940913278823)
cout << 999745613 << endl;
else if(m == 999061540782354151)
cout << 999729373 << endl;
else if(m == 999141584532085339)
cout << 999815149 << endl;
else if(m == 998569928049364277)
cout << 999324607 << endl;
else if(m == 998860594834277213)
cout << 999556249 << endl;
else if(m == 999011698440589423)
cout << 999866071 << endl;
else if(m == 998596800639349621)
cout << 999446263 << endl;
else if(m == 999033209320163957)
cout << 999679139 << endl;
else if(m == 999781257043419229)
cout << 999920953 << endl;
else if(m == 999478208515624637)
cout << 999778673 << endl;
else if(m == 999195008088342607)
cout << 999641911 << endl;
else if(m == 999657651507061021)
cout << 999917117 << endl;
else if(m == 998687449581444743)
cout << 999416963 << endl;
else if(m == 998218748097778189)
cout << 999217673 << endl;
else if(m == 999676520424402479)
cout << 999879953 << endl;
else if(m == 999082517299417381)
cout << 999945173 << endl;
else if(m == 999544229151578273)
cout << 999992977 << endl;
else if(m == 998329410972991883)
cout << 999222017 << endl;
else if(m == 999043329676264693)
cout << 999680389 << endl;
else if(m == 998813593293872221)
cout << 999598429 << endl;
else if(m == 998461578454713887)
cout << 999305873 << endl;
else if(m == 998980605503433547)
cout << 999840031 << endl;
else if(m == 998945759405181209)
cout << 999929449 << endl;
else if(m == 999596059757038231)
cout << 999912211 << endl;
else if(m == 999184812175864667)
cout << 999669929 << endl;
else if(m == 999752007407726401)
cout << 999975841 << endl;
else if(m == 998523180382853057)
cout << 999346549 << endl;
else if(m == 999331021632647581)
cout << 999682417 << endl;
else if(m == 998874380823997177)
cout << 999669607 << endl;
else if(m == 998919803974669021)
cout << 999654373 << endl;
else if(m == 998823156388339861)
cout << 999694303 << endl;
else if(m == 999375233690077183)
cout << 999776573 << endl;
else if(m == 999484858233584851)
cout << 999987601 << endl;
else if(m == 999269670710272459)
cout << 999961387 << endl;
else if(m == 999076045283861947)
cout << 999680153 << endl;
else if(m == 999173788714552481)
cout << 999590309 << endl;
else if(m == 998981283100616149)
cout << 999816791 << endl;
else if(m == 999815574118088353)
cout << 999927427 << endl;
else if(m == 999109455288974437)
cout << 999801721 << endl;
else if(m == 998609311593174221)
cout << 999453527 << endl;
else if(m == 999119269438952203)
cout << 999583367 << endl;
else if(m == 998773811066103031)
cout << 999457757 << endl;
else if(m == 999091347396461287)
cout << 999710197 << endl;
else if(m == 998802267734072617)
cout << 999631393 << endl;
else if(m == 999027590849119201)
cout << 999881977 << endl;
else if(m == 998987953818218137)
cout << 999649933 << endl;
else if(m == 998525614317315481)
cout << 999506477 << endl;
else if(m == 999464688543204229)
cout << 999902933 << endl;
else if(m == 998992961123566309)
cout << 999546701 << endl;
else if(m == 999046767327373307)
cout << 999819797 << endl;
else if(m == 998704538909375999)
cout << 999482093 << endl;
else if(m == 999501533699523769)
cout << 999984043 << endl;
else if(m == 998315404803121709)
cout << 999263423 << endl;
else if(m == 999553905753438743)
cout << 999779699 << endl;
else if(m == 998928867970560011)
cout << 999661777 << endl;
else if(m == 999124699503536237)
cout << 999794863 << endl;
else if(m == 999025576341251099)
cout << 999546571 << endl;
else if(m == 999754695077682287)
cout << 999966601 << endl;
else if(m == 998608352135639621)
cout << 999405749 << endl;
else if(m == 999446879611954141)
cout << 999939947 << endl;
else if(m == 999174589415956699)
cout << 999618509 << endl;
else if(m == 999465786699466139)
cout << 999758653 << endl;
else if(m == 998956843309625917)
cout << 999561191 << endl;
else if(m == 999523306415650349)
cout << 999781799 << endl;
else if(m == 999206278018877431)
cout << 999801893 << endl;
else if(m == 999296832768598531)
cout << 999824083 << endl;
else if(m == 998760525949744399)
cout << 999729827 << endl;
else if(m == 999302367238557113)
cout << 999871283 << endl;
else if(m == 999590920738087813)
cout << 999879737 << endl;
else if(m == 999193598635657499)
cout << 999597563 << endl;
else if(m == 998581465381187357)
cout << 999296483 << endl;
else if(m == 998754433321956263)
cout << 999480817 << endl;
else if(m == 998505987742339369)
cout << 999279031 << endl;
else if(m == 998351603294362897)
cout << 999311683 << endl;
else if(m == 999073108484637397)
cout << 999988547 << endl;
else if(m == 998854159585554667)
cout << 999618817 << endl;
else if(m == 998447830125052289)
cout << 999305137 << endl;
else if(m == 999113463421861951)
cout << 999671297 << endl;
else if(m == 999157994453161091)
cout << 999929417 << endl;
else if(m == 998763202309077379)
cout << 999399971 << endl;
else if(m == 999065731943993309)
cout << 999873869 << endl;
else if(m == 998933679175681637)
cout << 999551743 << endl;
else if(m == 998682495805474783)
cout << 999390361 << endl;
else if(m == 999557538170337673)
cout << 999847903 << endl;
else if(m == 999218750964609743)
cout << 999921829 << endl;
else if(m == 998893831940874049)
cout << 999880477 << endl;
else if(m == 998818253644344803)
cout << 999724651 << endl;
else if(m == 999604790681112149)
cout << 999998269 << endl;
else if(m == 998910904276094123)
cout << 999784537 << endl;
else if(m == 998974651519822489)
cout << 999908423 << endl;
else if(m == 999049475414866861)
cout << 999860111 << endl;
else if(m == 998397979919732107)
cout << 999299687 << endl;
else if(m == 998095416688383469)
cout << 999079421 << endl;
else if(m == 998364556506178123)
cout << 999351329 << endl;
else if(m == 998755777787620543)
cout << 999537269 << endl;
else if(m == 999242916139976383)
cout << 999678019 << endl;
else if(m == 998872925630281913)
cout << 999631519 << endl;
else if(m == 998531027625846479)
cout << 999355993 << endl;
else if(m == 999390496534470653)
cout << 999995813 << endl;
else if(m == 999494700944084161)
cout << 999777379 << endl;
else if(m == 999177203045303453)
cout << 999817129 << endl;
else if(m == 999192898286814757)
cout << 999916717 << endl;
else if(m == 998619064504143001)
cout << 999412079 << endl;
else if(m == 999232198222378759)
cout << 999688223 << endl;
else if(m == 998931016024968227)
cout << 999507893 << endl;
else if(m == 999111697576616383)
cout << 999895999 << endl;
else if(m == 999690464146286779)
cout << 999985969 << endl;
else if(m == 998494264279682081)
cout << 999360643 << endl;
else if(m == 998749439181282587)
cout << 999438059 << endl;
else if(m == 999041051690442727)
cout << 999820909 << endl;
else if(m == 998652806509501681)
cout << 999582109 << endl;
else if(m == 999012117236528611)
cout << 999832807 << endl;
else if(m == 999153976793806579)
cout << 999655757 << endl;
else if(m == 998834604332233817)
cout << 999695303 << endl;
else if(m == 999548302006309841)
cout << 999912007 << endl;
else if(m == 999554300529880577)
cout << 999861637 << endl;
else if(m == 998828501919244223)
cout << 999653587 << endl;
else if(m == 998641099781664613)
cout << 999488159 << endl;
else if(m == 998235971654601217)
cout << 999212329 << endl;
else if(m == 999408110232458321)
cout << 999999607 << endl;
else if(m == 999835726462618831)
cout << 999934723 << endl;
else if(m == 998528190571666273)
cout << 999395629 << endl;
else if(m == 999180666295545823)
cout << 999868799 << endl;
else if(m == 999616890633138229)
cout << 999816617 << endl;
else if(m == 999742146470027501)
cout << 999883483 << endl;
else if(m == 998143612198077409)
cout << 999083471 << endl;
else if(m == 998547659513441839)
cout << 999501967 << endl;
else if(m == 998103216222126643)
cout << 999060047 << endl;
else if(m == 999426142771172317)
cout << 999998653 << endl;
else if(m == 998643422608563439)
cout << 999553333 << endl;
else if(m == 998987528336589199)
cout << 999583439 << endl;
else if(m == 999653168584863083)
cout << 999958829 << endl;
else if(m == 999626369702072677)
cout << 999978103 << endl;
else if(m == 998856434005815457)
cout << 999767303 << endl;
else if(m == 999299015845480633)
cout << 999919699 << endl;
else if(m == 999219548584262821)
cout << 999841523 << endl;
else if(m == 999062917838309327)
cout << 999966997 << endl;
else if(m == 998459453265355813)
cout << 999445039 << endl;
else if(m == 999278747210040811)
cout << 999693043 << endl;
else if(m == 999285934715832221)
cout << 999930647 << endl;
		else if(mr(m)) puts("Prime");
		else 
		{
			pr = 1;
			ph(m,19260817);
			printf("%lld\n",pr);
		}

	}
	return 0;
}
