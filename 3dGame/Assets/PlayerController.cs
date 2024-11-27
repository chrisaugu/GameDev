using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PlayerController : MonoBehaviour
{
    private Vector3 velocity = Vector3.zero;
    private Rigidbody rb;
    private float speed = 5f;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update() => PerformMovement();

    private void PerformMovement()
    {
        float _xMov = Input.GetAxisRaw("Horizontal");
        float _yMov = Input.GetAxisRaw("Vertical");

        Vector3 _movHorizontal = transform.right * _xMov;
        Vector3 _movVertical = transform.forward * _yMov;

        Vector3 _velocity = (_movHorizontal + _movVertical).normalized * speed;

        if (_velocity != Vector3.zero)
        {
            rb.MovePosition(rb.position + _velocity * Time.fixedDeltaTime);
        }
    }
}
