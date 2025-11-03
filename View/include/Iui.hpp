class iUi
{
    /// @brief 新しいキーの情報を受け取り、画面上の表示を更新する
    /// @param newKey 
    virtual void updateKey(int newKey) = 0;

    /// @brief 回転キーによっていくつ右回転したのかを受け取り、画面上の表示を更新する
    /// @param rotateNum 
    virtual void updateRotateState(int rotateNum) = 0;
};