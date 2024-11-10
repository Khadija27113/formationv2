#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
using namespace std;
struct Member{
    int id;
    string firstName;
    string lastName;
    string role;
    bool operator<(const Member& other) const {
        return id < other.id; 
    }
};

 Member createMember(){
     Member newMember;
    
     cout<<"Enter ID : "<<endl;
     cin>>newMember.id;
     
     cout<<"Enter le prénom : "<<endl;
     cin>>newMember.firstName;
     
     cout<<"Enter le nom: "<<endl;
     cin>>newMember.lastName;
     
     cout<<"Enter le role: "<<endl;
     cin>>newMember.role;
     return newMember;
 } 
 void addMember(vector<Member> &members){
     Member tmp=createMember();
     members.push_back(tmp);
     
 }
 void addManyMembers(vector<Member> &members,int n){
     for(int i=0;i<n;i++){
        Member tmp=createMember();
        members.push_back(tmp);
     }
 }
 void deleteLastMember(vector<Member> &members){
     members.pop_back();
 }
 void deleteMemberById(vector<Member> &members,int id){
     auto it=members.begin();
     while((it!=members.end())&&(it->id!=id)){
         ++it;
         
     }
     if(it==members.end()){
         cout<<"le memebre avec ce ID est introuvable"<<endl;
     }else{
         members.erase(it);
     }
     
 }
 bool searchById(vector<Member> &members,int id){
     int i=0;
     while(i<members.size()){
         if(members[i].id==id){
             return true;
         }else{
             i++;
         }
     }
     return false;
     
 }
 void displayMemberById(vector<Member> &members,int id){
     int i=0;
     while(i<members.size()){
         if(members[i].id==id){
             cout<<members[i].id<<endl;
             cout<<members[i].firstName<<endl;
             cout<<members[i].lastName<<endl;
             cout<<members[i].role<<endl;
             return;

         }else{
             i++;
         }
     }
     cout<<"ce membre n'existe pas ";
 }
 void displayMemberByFirstName(vector<Member> &members,string firstName){
     int i=0;
     for(const auto& m :members){
         if(m.firstName==firstName){
             i++;
             cout<<"le membre num "<<i<<" ayant le nom "<<firstName;
             cout<<members[i].id<<endl;
             cout<<members[i].firstName<<endl;
             cout<<members[i].lastName<<endl;
             cout<<members[i].role<<endl;
         }
     }
     if(i==0){
         cout<<"on a aucun membre avec ce non";
     }
 }
 void addComponentFirstTime(map<int,pair<int,int>> &components){
     int ref;
     int total;
     cout<<"donner la reference de cette composent :"<<endl;
     cin>>ref;
     
     cout<<"donner la quantité totale :"<<endl;
     cin>>total;
     if(components.count(ref)){
         cout<<"cette composent existe déja ";
     }else{
         components.insert(make_pair(ref,make_pair(total,0)));
     }
 }
 void addComposant(map<int,pair<int,int>>& components, int id, int additionalQuantity){
     if(components.find(id)!=components.end()){
         components[id].first+=additionalQuantity;
     }else{
         cout<<"celle ci n'existe pas il faut l'ajouter d'abord ";
     }
 }
 bool composantIsAvailable(const map<int, pair<int,int>>& components, int id){
     if(components.find(id)!=components.end()){
         if(components.at(id).second<components.at(id).first){
            return true;
             
         }else{
             return false;
         }
     }else{
        return false;     }
 }
 bool isMemberAllocated(const set<Member>& allocatedMembers, int memberId){
     for(const auto& m:allocatedMembers){
         if(m.id==memberId){
             return true;}
     
 }
    return false; 
 }
 void allocateComposant(map<int,pair<int,int>>& components, set<Member>& allocatedMembers,const vector<Member>& members, int memberId, int composantId){
     if(isMemberAllocated(allocatedMembers,memberId)){
         cout<<"ce membre ne peut pas allouer un autre composent "<<endl;
         return;
     }
     else if (!composantIsAvailable(components, composantId)){
         cout << "Le composant avec ID " << composantId << " n'est pas disponible." << endl;
        return;
         
     }
     
     components[composantId].second+=1;
     bool found = false;
    for (const auto& member : members) {
        if (member.id == memberId) {
            allocatedMembers.insert(member);  
            found = true;
            break;
        }
    }
    if(!found){
       cout<<"le membre avec ID "<<memberId<<" est introuvable on doit l'ajouter d'abord" ;
    }
        
     }
 
 void displayAllocatedMembers(const set<Member>& allocatedMembers){
     for(const auto& m : allocatedMembers){
         cout<<m.id<<endl;
         cout<<m.firstName<<endl;
         cout<<m.lastName<<endl;
         cout<<m.role<<endl;
     }
 }
 
int main() {
    vector<Member> membres;
    map<int,pair<int,int>> components;
    set<Member> allocatedMembers;
    int choice;

    while (true) {
        cout << "\nSelect an option: " << endl;
        cout << "1. Add a member" << endl;
        cout << "2. Add many members" << endl;
        cout << "3. Delete last member" << endl;
        cout << "4. Delete member by ID" << endl;
        cout << "5. Search member by ID" << endl;
        cout << "6. Display member by ID" << endl;
        cout << "7. Display member by first name" << endl;
        cout << "8. Add component for the first time" << endl;
        cout << "9. Add more of an existing component" << endl;
        cout << "10. Check if component is available" << endl;
        cout << "11. Allocate component to member" << endl;
        cout << "12. Display allocated members" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember(membres);
                break;
            case 2: {
                int n;
                cout << "Enter number of members to add: ";
                cin >> n;
                addManyMembers(membres, n);
                break;
            }
            case 3:
                deleteLastMember(membres);
                break;
            case 4: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteMemberById(membres, id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                if (searchById(membres, id)) {
                    cout << "Member with ID " << id << " exists." << endl;
                } else {
                    cout << "Member with ID " << id << " does not exist." << endl;
                }
                break;
            }
            case 6: {
                int id;
                cout << "Enter ID to display: ";
                cin >> id;
                displayMemberById(membres, id);
                break;
            }
            case 7: {
                string firstName;
                cout << "Enter first name to search: ";
                cin >> firstName;
                displayMemberByFirstName(membres, firstName);
                break;
            }
            case 8:
                addComponentFirstTime(components);
                break;
            case 9: {
                int id, additionalQuantity;
                cout << "Enter component ID: ";
                cin >> id;
                cout << "Enter additional quantity: ";
                cin >> additionalQuantity;
                addComposant(components, id, additionalQuantity);
                break;
            }
            case 10: {
                int id;
                cout << "Enter component ID to check: ";
                cin >> id;
                if (composantIsAvailable(components, id)) {
                    cout << "Component is available." << endl;
                } else {
                    cout << "Component is not available." << endl;
                }
                break;
            }
            case 11: {
                int memberId, composantId;
                cout << "Enter member ID: ";
                cin >> memberId;
                cout << "Enter component ID: ";
                cin >> composantId;
                allocateComposant(components, allocatedMembers, membres, memberId, composantId);
                break;
            }
            case 12:
                displayAllocatedMembers(allocatedMembers);
                break;
            case 13:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
    

    return 0;
}
