//
//  Level_1.h
//  
//
//  Created by Spanky Clayton on 4/8/15.
//
//

class Level_1 : public Layer
{
public:
    Level_1(void);
    ~Level_1(void);
    
    CREATE_FUNC(Level_1);
    
    static Scene* createScene();
    
    virtual bool init() override;
    
    void toLevel1();
};
