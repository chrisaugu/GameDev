using UnityEngine;

[RequireComponent(typeof(MovementController))]
public class Player : MonoBehaviour
{

    [SerializeField]
    private int _lives = 3;
    private int _coins = 0;
    private UIManager _uiManager;

    private MovementController _controller;

    void Start()
    {
        _controller = GetComponent<MovementController>();
        _uiManager = GameObject.Find("Canvas").GetComponent<UIManager>();
        if (_uiManager == null)
        {
            Debug.LogError("The UI Manager is null");
        }
        else
        {
            _uiManager.UpdateCoinDisplay(_coins);
            _uiManager.UpdateLivesDisplay(_lives);
        }
    }

}
