#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/* STATEMACHINE.H
here are all the state machine related functions */


// function prototypes


void set_animation(Entity *entity)
{
    if (entity->state == IDLE) sausage64_set_anim(entity->helper, ANIMATION_nick_idle);
    if (entity->state == WALK) sausage64_set_anim(entity->helper, ANIMATION_nick_walk);
    if (entity->state == RUN) sausage64_set_anim(entity->helper, ANIMATION_nick_run);
}




void set_entity_state(Entity * entity, entity_state new_state) 
{
    if (entity->state == new_state) return;

    entity->state = new_state;

    set_animation(entity);
}

void handle_entity_actions(NUContData cont[1], Entity* entity){

    // U_CBUTTONS
    
    if (cont[0].trigger & R_TRIG) {}

    if (cont[0].trigger & A_BUTTON) set_entity_state(entity, JUMP);
    
    if (cont[0].trigger & B_BUTTON) set_entity_state(entity, ROLL);

    if (cont->stick_x == 0 && cont->stick_y == 0
        && entity->entity.state != JUMP 
        && entity->entity.state != ROLL
        && entity->entity.state != FALLBACK
        && entity->entity.state != FALL 
        && entity->entity.state != MIDAIR 
        ) {
        set_entity_state(entity, IDLE);
    }

}