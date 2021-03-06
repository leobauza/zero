<?php
/**
 * @file
 * Preprocessors.
 *
 * The zero theme requires the Nil namespace provided by the nil module.
 *
 * @see
 *   /modules/custom/nil
 */

/**
 * Implements hook_preprocess_html().
 */
function zero_preprocess_html(&$vars) {

  $menus = array(
    "main-menu",
  );
  // Retrieve Menus.
  $main_menu = Nil\Theme::getMenus($menus);

  $vars["main_menu"] = $main_menu;

}

/**
 * Implements hook_preprocess_page().
 */
function zero_preprocess_page(&$vars) {
  // Preprocess page template.
  if (isset($vars["node"])) {
    $node = $vars["node"];
    $node_type = $node->type;
    if (!$vars['is_front']) {
      $vars['theme_hook_suggestions'][] = 'page__' . $node_type;
    }
    // Zero entity that wraps around the entity_metadata_wrapper.
    $entity = $vars["entity"] = new Nil\Entity($node, $node_type);
    // Fields array for easier isset checking. (maybe good?).
    $fields = $vars["fields"] = $entity->getFieldsArray();
    // The entity_metadata_wrapper we wrapped around. (inception).
    $wrapper = $vars["wrapper"] = $entity->getWrapper();
  }
}

/**
 * Implements hook_preprocess_node().
 */
function zero_preprocess_node(&$vars) {
  // Replace classes array with our own classes.
  $vars["classes_array"] = array("node");
}
